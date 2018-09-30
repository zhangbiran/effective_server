#ifndef __dataanalyzer_h
#define __dataanalyzer_h

class DataCollector;
class DataContainer;
class RemoteIODataContainer;

struct OneQuestData
{
	OneQuestData() : _buf(0), _size(0), _dataCollector(0)
	{

	}

	char* _buf;
	int _size;
	DataCollector* _dataCollector;
};

class DataAnalyzer
{
public:
	static DataAnalyzer* instance();
	virtual OneQuestData analyzer(DataContainer* dataContainer);
	virtual OneQuestData analyzerRemoteIODataContainer(RemoteIODataContainer* dataContainer);

private:
	DataAnalyzer();
	virtual ~DataAnalyzer();
	static DataAnalyzer* _instance;
};


#endif