#include "stream.h"

Stream::Stream(char* buf, int size)
{
	init(buf, size);
}

void Stream::init(char*buf, int size)
{
	_buf = buf;
	_size = size;
	_writePos = 0;
	_readPos = 0;
}

char Stream::readChar()
{
	if (!hasUnReadSize(sizeof(char)))
		return 0;

	char*p = _buf + _readPos;
	addReadPos(sizeof(char));
	return *((char*)p);
}

short Stream::readShort()
{
	if (!hasUnReadSize(sizeof(short)))
		return 0;

	char*p = _buf + _readPos;
	addReadPos(sizeof(short));
	return *((short*)p);
}

int Stream::readInt()
{
	if (!hasUnReadSize(sizeof(int)))
		return 0;

	char*p = _buf + _readPos;
	addReadPos(sizeof(int));
	return *((int*)p);
}

float Stream::readFloat()
{
	if (!hasUnReadSize(sizeof(float)))
		return 0;

	char*p = _buf + _readPos;
	addReadPos(sizeof(float));
	return *((float*)p);
}

double Stream::readDouble()
{
	if (!hasUnReadSize(sizeof(double)))
		return 0;

	char*p = _buf + _readPos;
	addReadPos(sizeof(double));
	return *((double*)p);
}

long long Stream::readLongLong()
{
	if (!hasUnReadSize(sizeof(long long)))
		return 0;

	char*p = _buf + _readPos;
	addReadPos(sizeof(long long));
	return *((long long*)p);
}


void Stream::writeChar(char v)
{
	if (!hasUnWriteSize(sizeof(char)))
		return;

	char*p = _buf + _writePos;
	addWritePos(sizeof(char));
	*((char*)p) = v;
}

void Stream::writeShort(short v)
{
	if (!hasUnWriteSize(sizeof(short)))
		return;

	char*p = _buf + _writePos;
	addWritePos(sizeof(short));
	*((short*)p) = v;
}

void Stream::writeInt(int v)
{
	if (!hasUnWriteSize(sizeof(int)))
		return;

	char*p = _buf + _writePos;
	addWritePos(sizeof(int));
	*((int*)p) = v;
}

void Stream::writeFloat(float v)
{
	if (!hasUnWriteSize(sizeof(float)))
		return;

	char*p = _buf + _writePos;
	addWritePos(sizeof(float));
	*((float*)p) = v;
}

void Stream::writeDouble(double v)
{
	if (!hasUnWriteSize(sizeof(double)))
		return;

	char*p = _buf + _writePos;
	addWritePos(sizeof(double));
	*((double*)p) = v;
}

void Stream::writeLongLong(long long v)
{
	if (!hasUnWriteSize(sizeof(long long)))
		return;

	char*p = _buf + _writePos;
	addWritePos(sizeof(long long));
	*((long long*)p) = v;
}

char *Stream::getBuf()
{
	return _buf;
}

int Stream::getSize()
{
	return _size;
}

void Stream::addWritePos(int n)
{
	_writePos += n;
	if (_writePos >= _size)
		_writePos = _size;
}

void Stream::addReadPos(int n)
{
	_readPos += n;
	if (_readPos >= _size)
		_readPos = _size;
}

bool Stream::hasUnWriteSize(int n)
{
	if (_writePos + n <= _size)
		return true;
	return false;
}

bool Stream::hasUnReadSize(int n)
{
	if (_readPos + n <= _size)
		return true;
	return false;
}
