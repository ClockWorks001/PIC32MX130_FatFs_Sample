/*******************************************************************************
 *	FIFO buffer for serial data
 *	author  :hiroshi murakami
 *	created :20160827
 *	modified:-
 ******************************************************************************/

#include "string.h"
#include "integer.h"
#include "vFIFO.h"


// Check number of bytes in the FIFO 
int  vFifo_test (
    FIFO_STRUCT* Fifo
){
    return Fifo->ct;   // Return number of bytes in the FIFO 
}

// return space size of bytes in the FIFO 
int  vFifo_spaceSize (
    FIFO_STRUCT* Fifo
){
    return (Fifo->buffer_size - Fifo->ct); 
}

// Get a byte from FIFO *return a data from buffer
BYTE vFifo_getc (
    FIFO_STRUCT* Fifo
){
    BYTE d;
    int i;

    Fifo->status = IS_FIFO_BUFFER_STORED;
    if (!Fifo->ct) {          	//when FIFO buffer empty */
        Fifo->status = IS_FIFO_BUFFER_EMPTY;
        return 0x00;
    }

    i = Fifo->ri;             	// Get a byte from FIFO 
    d = Fifo->buffer[i++];
    Fifo->ri = i % Fifo->buffer_size;
    Fifo->ct--;

    return d;					//return a data
}

// Put a byte into FIFO *return a status
int vFifo_putc (
    FIFO_STRUCT* Fifo, 
    BYTE d
){
    int i;

    if (Fifo->ct >= Fifo->buffer_size) {       	// Return when FIFO is full 
        Fifo->status = IS_FIFO_BUFFER_FULL;
        return  IS_FIFO_BUFFER_FULL;
    }

    Fifo->status = 0;
    i = Fifo->wi;     				// Put a data into the FIFO 
    Fifo->buffer[i++] = d;
    Fifo->wi = i % Fifo->buffer_size;
    Fifo->ct++;
    return  IS_FIFO_BUFFER_STORED;
   
}

// Initialize FIFO instance
void vFifo_init (
    FIFO_STRUCT* Fifo, 
    int buffer_size, 
    BYTE* buffer
){
    /* Clear FIFOs */
    Fifo->ri = 0; 
    Fifo->wi = 0; 
    Fifo->ct = 0; 
    Fifo->status = 0;
    Fifo->buffer_size = buffer_size; 
    Fifo->buffer = buffer; 
//    memset( &(Fifo->buff) , 0x00 , Fifo->buffer_size );
    memset( (Fifo->buffer) , 0x00 , Fifo->buffer_size );
}


