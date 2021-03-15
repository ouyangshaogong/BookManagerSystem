#ifndef __DATA_MODEL__
#define __DATA_MODEL__

class DataModel
{
public:
    int GetLevel();
    void SetLevel(int nLevel);
private:
    int m_nLevel;
};

#endif