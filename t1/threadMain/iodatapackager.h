#ifndef __io_data_handler_h
#define __io_data_handler_h


class DataContainer;

class IODataPackager
{
public:
	virtual ~IODataPackager() {}
	virtual void handlerIOData(DataContainer* dataContainer) = 0;
};

#endif