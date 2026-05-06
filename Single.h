#pragma once
#include "Defines.h"
class Single
{
private:
	Single();
public :
	static Single* GetInst() 
	{
		if (nullptr == m_inst)
			m_inst = new Single();
		return m_inst;
	}
	static void DestroyInst() {
		SAFE_DELETE(m_inst);
	}
private:
	static Single* m_inst;
};

