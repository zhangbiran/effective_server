#include "dataanalyzer.h"
#include "datacontainer.h"

DataAnalyzer* DataAnalyzer::_instance = new DataAnalyzer();

DataAnalyzer::DataAnalyzer()
{

}

DataAnalyzer::~DataAnalyzer()
{

}

DataAnalyzer* DataAnalyzer::instance()
{
	return _instance;
}

OneQuestData DataAnalyzer::analyzer(DataContainer*dataContainer)
{
	return dataContainer->beAnalyzer(this);
}

OneQuestData DataAnalyzer::analyzerRemoteIODataContainer(RemoteIODataContainer* dataContainer)
{
	OneQuestData data;
	data._buf = dataContainer->_buf;
	data._size = 100;
	data._dataCollector = dataContainer->getDataCollector();
	return data;
}
