// You are given a raw byte buffer received from a hardware/network interface.

// The first 8 bytes are the packet header:

// Byte 0      : version
// Byte 1      : message type
// Bytes 2-3   : payload length, big-endian
// Bytes 4-7   : sequence number, big-endian

// Write a C++ function to parse the header.

// The function should:
// 1. Check that the buffer is not null.
// 2. Check that the buffer has at least 8 bytes.
// 3. Extract all header fields.
// 4. Check that the full packet exists, meaning:
//    total size >= header size + payload length.
// 5. Return true if parsing succeeds, false otherwise.



#include <cstdint>
#include <cstddef>
#include <iostream>

using namespace std;

constexpr size_t HEADER_SIZE = 8;

struct PacketHeader {
	uint8_t version;
	uint8_t type;
	uint16_t payload_length;
	uint32_t sequence_number;
};

bool parsePacketHeader(const uint8_t* buffer,
					   size_t buffer_size,
					   PacketHeader& header) 
{
	// 1. Check for null buffer
	if (buffer == nullptr)
	{
		// cout << "Empty Buffer";	
		return false;
	}
	
	// 2. Check if buffer has at least header size
	if (buffer_size < HEADER_SIZE)
	{
		// cout << "Invalid Packet";
		return false;
	}

	
	const uint8_t* buffer_ptr = buffer;
	// 3. Parse version
	header.version = *buffer_ptr;
	buffer_ptr = buffer_ptr + 1;	// Move pointer by 1 byte
	
	// 4. Parse type
	header.type = *buffer_ptr;
	buffer_ptr = buffer_ptr + 1;	// Move pointer by 1 byte
	

	// 5. Parse payload length
	// Bytes 2 and 3, big-endian
	
	/*
		buffer_ptr: Holds Byte 2: The MSB Byte
		buffer_ptr + 1: Holds Byte 3: The LSB Byte
		Important: rvalue always follows the order of LSB ==> MSB from right to left. 
		rvalue does not have any enddianness as such. Endianness is about how something is stored in memory. rvalue is just an abstract human representation. (Think of decimal number 234. It is always WRITTEN LSB to MSB right to left) 
		So for the 2 bytes: In packet, If byte-1 is : A, and byte-2 is: B. The actual number for humans: 0x(AB)
		So you take the 2 bytes from the packet, convert it to rvlaue representation (LSB --> MSB : Right to Left)
		Store this rvalue in a struct variable. The CPU will take care of storing this rvalue in the struct variable in whatever endianness it uses (we do not know). 
		header.payload_length = (static_cast<uint16_t>( *buffer_ptr )) << 8 | static_cast<uint16_t> ( *(buffer_ptr+1) ); 
		*/   
	buffer_ptr = buffer_ptr + 2;	// update the buffer_ptr
	
	// 6. Parse sequence number
	// Bytes 4, 5, 6, 7, big-endian
	
	// Put Byte-4 at MSB Byte-3 of rval, byte-5 at byte-2, byte-6 at byte-1, byte-7 at byte-0
	header.sequence_number = (static_cast<uint32_t>( *buffer_ptr ) << 24) | (static_cast<uint32_t>( *(buffer_ptr+1) ) << 16) | (static_cast<uint32_t>( *(buffer_ptr+2) ) << 8) | (static_cast<uint32_t> (*(buffer_ptr+3))) ;
	buffer_ptr = buffer_ptr + 4;

	// 7. Check whether full packet is available
	// buffer_size should be >= 8 + payload_length
	if (buffer_size < 8 + header.payload_length)
		return false;

	// 8. Return true if all checks pass
	return true;
}