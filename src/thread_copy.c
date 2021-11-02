
#include "cmsis_os.h"  // CMSIS RTOS header file
#include "Board_LED.h"
#include "UART_driver.h"
#include "stdint.h"                     // data type definitions
#include "stdio.h"                      // file I/O functions
#include "rl_usb.h"                     // Keil.MDK-Pro::USB:CORE
#include "rl_fs.h"                      // Keil.MDK-Pro::File System:CORE
#include "stm32f4xx_hal.h"
#include "stm32f4_discovery.h"
#include "stm32f4_discovery_audio.h"
#include <stdio.h>

#define LED_Green   0
#define LED_Orange  1
#define LED_Red     2
#define LED_Blue    3

typedef struct WAVHEADER {
	unsigned char riff[4];						// RIFF string
	uint32_t overall_size;				// overall size of file in bytes
	unsigned char wave[4];						// WAVE string
	unsigned char fmt_chunk_marker[4];		// fmt string with trailing null char
	uint32_t length_of_fmt;					// length of the format data
	uint16_t format_type;					// format type. 1-PCM, 3- IEEE float, 6 - 8bit A law, 7 - 8bit mu law
	uint16_t channels;						// no.of channels
	uint32_t sample_rate;					// sampling rate (blocks per second)
	uint32_t byterate;						// SampleRate * NumChannels * BitsPerSample/8
	uint16_t block_align;					// NumChannels * BitsPerSample/8
	uint16_t bits_per_sample;				// bits per sample, 8- 8bits, 16- 16 bits etc
	unsigned char data_chunk_header [4];		// DATA string or FLLR string
	uint32_t data_size;						// NumSamples * NumChannels * BitsPerSample/8 - size of the next chunk that will be read
} WAVHEADER;


#define Show_Files_char "1"
#define Get_Selected_Char "4"
#define Play_Char "5"
#define Pause_Char "6"
#define Resume_Char "7"
#define Stop_Char "8"

#define FILENAME_MAX_CHARS 256
char selectedFile[FILENAME_MAX_CHARS] = "Fly me To The Moon.wav";

#define NUM_CHAN	2 // number of audio channels
#define NUM_SAMPLES 1024 // number of points per channel
#define BUF_LEN NUM_CHAN*NUM_SAMPLES // length of the audio buffer
/* buffer used for audio play */
int16_t Audio_Buffer[BUF_LEN];
int16_t Audio_Buffer1[BUF_LEN];
uint32_t Mute_Buffer[BUF_LEN/2];

// pointer to file type for files on USB device
FILE *f;

// Command queue from Rx_Command to Controller
osMessageQId mid_CMDQueue; // message queue for commands to Thread
osMessageQDef (CMDQueue, 1, uint32_t); // message queue object

// Command queue from Controller Blue_Blink_Thread
osMessageQId mid_Command_FsQueue; // message queue for commands to Thread
osMessageQDef (Command_FsQueue, 1, uint32_t); // message queue object]

// Command queue from Fs to DMA
osMessageQId mid_DMAQueue; // message queue for commands to Thread
osMessageQDef (DMAQueue, 1, uint32_t); // message queue object

osMessageQId mid_PRQueue; // message queue for commands to Thread
osMessageQDef (PRQueue, 1, uint32_t); // message queue object

osSemaphoreDef (dma_semaphore);    // Declare semaphore
osSemaphoreId  (dma_semaphore_id); // Semaphore ID

//////////////////////////////////////////////////////////
void Fs (void const *argument); // thread function
osThreadId tid; // thread id
osThreadDef (Fs, osPriorityNormal, 1, 0); // thread object

void Control (void const *argument); // thread function
osThreadId tid1; // thread id
osThreadDef (Control, osPriorityAboveNormal, 1, 0); // thread object

void Rx_Command (void const *argument); // thread function
osThreadId tid2; // thread id
osThreadDef (Rx_Command, osPriorityAboveNormal, 1, 0); // thread object


void Process_Event(uint16_t event);

enum commands{
  ListFiles,
  SendComplete,
  SendFiles,
  PlayFile,
  PlayingFinished,
  PausePlaying,
  ResumePlaying,
  StopPlaying
};

enum states{
	NoState,
	Idle,
	List,
	Playing,
	Paused
};

void Init_Thread (void) {
   LED_Initialize(); // Initialize the LEDs
   UART_Init(); // Initialize the UART

   mid_CMDQueue = osMessageCreate (osMessageQ(CMDQueue), NULL);  // create msg queue
     if (!mid_CMDQueue)return; // Message Queue object not created, handle failure

   mid_Command_FsQueue = osMessageCreate (osMessageQ(Command_FsQueue), NULL);  // create msg queue
     if (!mid_Command_FsQueue)return; // Message Queue object not created, handle failure

  mid_DMAQueue = osMessageCreate (osMessageQ(DMAQueue), NULL);  // create msg queue
     if (!mid_DMAQueue)return; // Message Queue object not created, handle failure

   mid_PRQueue = osMessageCreate (osMessageQ(PRQueue), NULL);  // create msg queue
     if (!mid_PRQueue)return; // Message Queue object not created, handle failure

   dma_semaphore_id = osSemaphoreCreate(osSemaphore(dma_semaphore), 0);  // Create semaphore with 0 tokens
  // Create threads
   tid = osThreadCreate (osThread(Fs), NULL);
   if (!tid) return;


   tid1 = osThreadCreate (osThread(Control), NULL);
   if (!tid1) return;


   tid2 = osThreadCreate (osThread(Rx_Command), NULL);
   if (!tid2) return;
}
void Process_Event(uint16_t event)
{
  static uint16_t   Current_State = NoState; // Current state of the SM
  osEvent evt;
  switch(Current_State){
    case NoState:
      // Next State
      Current_State = Idle;
      // Exit actions
      // Transition actions
      // State1 entry actions
      LED_On(LED_Red);

      break;
    case Idle:
      if(event == ListFiles)
      {
        Current_State = List;
        // Exit actions
        LED_Off(LED_Red);
        // Transition actions
        // State2 entry actions
        LED_On(LED_Blue);
        osMessagePut(mid_Command_FsQueue, SendFiles,osWaitForever);
      }
      if(event == PlayFile)
      {
    	  Current_State = Playing;
    	  osMessagePut(mid_Command_FsQueue, PlayFile,osWaitForever);
      }
      break;
    case List:
      if(event == SendComplete){
        Current_State = Idle;
        // Exit actions
        LED_Off(LED_Blue);
        // Transition actions
        // State1 entry actions
        LED_On(LED_Red);
      }
      break;
    case Playing:
    	if(event == PlayingFinished)
    	{
    		Current_State = Idle;
    	}
    	else if(event  == PausePlaying)
    	{
    		Current_State = Paused;
    		osMessagePut(mid_PRQueue, PausePlaying,osWaitForever);
    	}
    	else if(event == StopPlaying)
    	{
    		Current_State = Idle;
    		osMessagePut(mid_PRQueue, StopPlaying,osWaitForever);
    	}
    	break;
    case Paused:
    	if(event == ResumePlaying)
    	{
    		Current_State = Playing;
    		osMessagePut(mid_PRQueue, ResumePlaying,osWaitForever);
    	}
    	break;
    default:
      break;
  } // end case(Current_State)
} // Process_Event

// Thread function
void Control(void const *arg)
{
  osEvent evt; // Receive message object
  Process_Event(0); // Initialize the State Machine
   while(1){
    evt = osMessageGet (mid_CMDQueue, osWaitForever); // receive command
      if (evt.status == osEventMessage) { // check for valid message
      Process_Event(evt.value.v); // Process event
    }
   }
}

// User Callbacks: user has to implement these functions if they are needed.
// This function is called when the requested data has been completely transferred.
void BSP_AUDIO_OUT_TransferComplete_CallBack(void)
{
	uint32_t buffNum = 2;
	osEvent evt;
	//getMessage
	evt = osMessageGet (mid_DMAQueue, 0); // receive command
	if (evt.status == osEventMessage)
	{ // check for valid message
	   buffNum = evt.value.v; // Process event
	}
	else
	{
		buffNum = 200;
	}
	//Change Streaming Buffer
	if(buffNum == 0)
	{
		BSP_AUDIO_OUT_ChangeBuffer((uint16_t *)Audio_Buffer, BUF_LEN);
		//release semaphore putting Thread_q in the ready state
		osSemaphoreRelease(dma_semaphore_id);
	}
	else if(buffNum == 1)
	{
		BSP_AUDIO_OUT_ChangeBuffer((uint16_t *)Audio_Buffer1, BUF_LEN);
		//release semaphore putting Thread_q in the ready state
		osSemaphoreRelease(dma_semaphore_id);
	}
	else
	{
		BSP_AUDIO_OUT_ChangeBuffer((uint16_t *)Audio_Buffer1, BUF_LEN);
	}
}

//This function is called when half of the requested buffer has been transferred.
void BSP_AUDIO_OUT_HalfTransfer_CallBack(void)
{

}

//This function is called when an Interrupt due to transfer error or peripheral
  // error occurs.
void BSP_AUDIO_OUT_Error_CallBack(void)
{
	while(1)
	{
		UART_send("F\n\r",3);
	}
}

void Rx_Command (void const *argument)
{
   char rx_char[2]={0,0};

   while(1)
   {
      UART_receive(rx_char, 1); // Wait for command from PC GUI
    // Check for the type of character received
      if(!strcmp(rx_char,Show_Files_char))
      {
         // Trigger1 received
         osMessagePut (mid_CMDQueue, ListFiles, osWaitForever);
      }
      else if(!strcmp(rx_char,Get_Selected_Char))
      {
               // Trigger1 received
               UART_receivestring(selectedFile, FILENAME_MAX_CHARS);
      }
      else if(!strcmp(rx_char,Play_Char))
      {
    	  osMessagePut (mid_CMDQueue, PlayFile, osWaitForever);
      }
      else if(!strcmp(rx_char,Pause_Char))
      {
    	  osMessagePut (mid_CMDQueue, PausePlaying, osWaitForever);
      }
      else if(!strcmp(rx_char,Resume_Char))
      {
    	  osMessagePut (mid_CMDQueue, ResumePlaying, osWaitForever);
      }
      else if(!strcmp(rx_char,Stop_Char))
      {
    	  osMessagePut (mid_CMDQueue, StopPlaying, osWaitForever);
      }
   }
} // end Rx_Command
void Fs (void const *argument){
	usbStatus ustatus; // USB driver status variable
		uint8_t drivenum = 0; // Using U0: drive number
		char *drive_name = "U0:"; // USB drive name

		fsStatus fstatus; // file system status variable

		fsFileInfo info;
		info.fileID = 0;

		WAVHEADER header;
		size_t rd;
		uint32_t i;
		static uint8_t rtrn = 0;
		uint8_t rdnum = 1; // read buffer number
		int16_t* curBuffPtr = Audio_Buffer;
		uint32_t buffNum = 0;
		uint8_t playFag = 1;
		size_t numRead = 0;

		uint8_t initFlag = 0;

		LED_On(LED_Green);
		ustatus = USBH_Initialize (drivenum); // initialize the USB Host
		if (ustatus == usbOK){
			// loop until the device is OK, may be delay from Initialize
			ustatus = USBH_Device_GetStatus (drivenum); // get the status of the USB device
			while(ustatus != usbOK){
				ustatus = USBH_Device_GetStatus (drivenum); // get the status of the USB device
			}
			// initialize the drive
			fstatus = finit (drive_name);
			if (fstatus != fsOK){
				// handle the error, finit didn't work
			} // end if
			// Mount the drive
			fstatus = fmount (drive_name);
			if (fstatus != fsOK){
				// handle the error, fmount didn't work
			} // end if
			// file system and drive are good to go
			osEvent evt;
			while(1)
			{
			evt = osMessageGet (mid_Command_FsQueue, osWaitForever); // receive command
			if (evt.status == osEventMessage)
			{
				if(evt.value.v == SendFiles)
				{
				    		info.fileID = 0;
				    	  	UART_send("2\n",2);
				    	  	while(ffind ("U0:*.wav", &info) == fsOK)
				    	  	{
				    	  			UART_send(info.name, strlen(info.name));
				    	  			UART_send("\n", 1);
				    	  	}
				    	  	UART_send("3\n",2);
				    	  	osMessagePut (mid_CMDQueue, SendComplete, osWaitForever);
				}
				else if (evt.value.v == PlayFile)
				{
							f = fopen (selectedFile,"r");// open a file on the USB device
							if (f != NULL)
							{
								fread((void *)&header, sizeof(header), 1, f);
							} // end if file opened
							if(!initFlag)
							{
								//call BSP_AUDIO_OUT_Init()
								rtrn = BSP_AUDIO_OUT_Init(OUTPUT_DEVICE_AUTO, 75, header.sample_rate);
								if (rtrn == AUDIO_ERROR)
								{
									return;
								}
							}

							//read in first buffer
							curBuffPtr = Audio_Buffer;
							numRead = fread((void*)&Audio_Buffer, sizeof(int16_t), BUF_LEN, f);
							if(numRead < BUF_LEN)
							{
								fclose(f);
								f = NULL;
							}

						 	curBuffPtr = Audio_Buffer1;
						 	buffNum = 1;
						 	//set the sample frequency
						 	/*if(header.sample_rate == 44100)
						 	{
						 		BSP_AUDIO_OUT_SetFrequency(header.sample_rate);
						 	}*/
							// Start the audio player, size is number of bytes so mult. by 2
						 	if(!initFlag)
						 	{
						 		BSP_AUDIO_OUT_Play((uint16_t *)Audio_Buffer, BUF_LEN*2);
						 		initFlag = 1;
						 	}
						 	else
						 	{
						 		BSP_AUDIO_OUT_SetMute(AUDIO_MUTE_OFF);
						 		BSP_AUDIO_OUT_ChangeBuffer((uint16_t *)Audio_Buffer, BUF_LEN);
						 	}
							//continuously switch
							while(f != NULL)
							{
								evt = osMessageGet (mid_PRQueue, 0); // receive command
								if (evt.status == osEventMessage)
								{
									if(evt.value.v == PausePlaying)
									{
										playFag = 0;
										BSP_AUDIO_OUT_SetMute(AUDIO_MUTE_ON);
										//BSP_AUDIO_OUT_Pause();
									}
									else if(evt.value.v == ResumePlaying)
									{
										playFag = 1;
										//BSP_AUDIO_OUT_Resume();
										BSP_AUDIO_OUT_SetMute(AUDIO_MUTE_OFF);
									}
									else
									{
										playFag = 0;
										BSP_AUDIO_OUT_SetMute(AUDIO_MUTE_ON);
										fclose(f);
										f = NULL;
										//BSP_AUDIO_OUT_Stop(CODEC_PDWN_HW);
									}
								}
								if(playFag)
								{
									numRead = fread((void*)curBuffPtr, sizeof(int16_t), BUF_LEN, f);
									if(numRead < BUF_LEN)
									{
										fclose(f);
										f = NULL;
										playFag = 2;
										//BSP_AUDIO_OUT_Stop(CODEC_PDWN_HW);
										//osMessagePut(mid_CMDQueue, 2, osWaitForever); //possibly change osWaitForever to 0

									}
									//send next buffer message
									osMessagePut(mid_DMAQueue, buffNum, osWaitForever); //possibly change osWaitForever to 0
									//block on semaphore
									osSemaphoreWait(dma_semaphore_id, osWaitForever);
									//switch buffers
									if(buffNum == 1)
									{
										curBuffPtr = Audio_Buffer;
										buffNum = 0;
									}
									else
									{
										curBuffPtr = Audio_Buffer1;
										buffNum = 1;
									}
									if(playFag == 2)
									{
										osMessagePut (mid_CMDQueue, PlayingFinished, osWaitForever);
									}
								}
								else if(!playFag)
								{
									/*//send next buffer message
									osMessagePut(mid_DMAQueue, 1, osWaitForever); //possibly change osWaitForever to 0
									//block on semaphore
									osSemaphoreWait(dma_semaphore_id, osWaitForever);*/

								}
							}
						 	osMessagePut (mid_CMDQueue, PlayingFinished, osWaitForever);
			  	  }
		} // end if USBH_Initialize
		}
		LED_Off(LED_Green);
		}
}
