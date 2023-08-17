#include "DictProducer.h"
#include "MyLogger.h"

int main()
{
    
    DictProducer enDict("../conf/en");
    
    enDict.readStopWords("stop_words_eng.txt");
    enDict.buildEnDict();

    cout << "222" << endl;
    enDict.storeDict("../data/dict_en.txt");

}
