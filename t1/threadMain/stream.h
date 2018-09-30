#ifndef __stream_h
#define __stream_h

class Stream
{
public:
	Stream(char* buf = 0, int size = 0);
	void init(char*buf, int size);

	char readChar();
	short readShort();
	int readInt();
	float readFloat();
	double readDouble();
	long long readLongLong();

	void writeChar(char v);
	void writeShort(short v);
	void writeInt(int v);
	void writeFloat(float v);
	void writeDouble(double v);
	void writeLongLong(long long v);


	char *getBuf();
	int getSize();

private:
	void addWritePos(int n);
	void addReadPos(int n);
	bool hasUnWriteSize(int n);
	bool hasUnReadSize(int n);

	char* _buf;
	int _size;
	int _writePos;
	int _readPos;
};

#endif
