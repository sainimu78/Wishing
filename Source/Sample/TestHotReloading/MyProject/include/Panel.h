#pragma once
#include "Script.h"
#include "Panel_gen.h"

NIF_T()
class CPanel : public Wishing::CScript
{
	GENERATED_BODY()
public:
	virtual void Execute() override;
};