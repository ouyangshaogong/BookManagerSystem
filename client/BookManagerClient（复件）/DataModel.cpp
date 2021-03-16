#include "DataModel.h"
DataModel::DataModel()
    :m_nLevel(0)
{

}
void DataModel::SetLevel(int nLevel)
{
    m_nLevel = nLevel;
}

int DataModel::GetLevel()
{
    return m_nLevel;
}
