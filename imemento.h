#ifndef IMEMENTO_H
#define IMEMENTO_H

#include <QStack>

class IMemento
{
public:
   virtual void restoreData()=0;
   virtual ~IMemento(){};
};

class MementoCollector
{
public:
   static void addBack(IMemento* newMem)
   {
        m_back.push(newMem);
   }
   static void addAhead(IMemento* newMem)
   {
        m_ahead.push(newMem);
   }
   static void restoreBack()
   {
        if (!m_back.isEmpty())
        {
            IMemento* mem = m_back.pop();
            mem->restoreData();
        }
   }
   static void restoreAhead()
   {
       if (!m_ahead.isEmpty())
       {
            IMemento* mem = m_ahead.pop();
            mem->restoreData();
       }
   }
   static unsigned getBackSize()
   {
       return m_back.size();
   }
   static unsigned getAheadSize()
   {
       return m_ahead.size();
   }
   static void clearBack()
   {
       m_back.clear();
   }
   static void clearAhead()
   {
       m_ahead.clear();
   }
private:
   static QStack<IMemento*> m_back;
   static QStack<IMemento*> m_ahead;
   MementoCollector();
};

#endif // IMEMENTO_H
