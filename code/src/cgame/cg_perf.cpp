#include "types.h"

CG_PerfInfo cg_perfInfo;

int previousMS;
unsigned __int64 gRunFrameTicks;
long double msecPerRawTimerTick;
int gLastScrExecuteTime[2];
int dword_7DCED84;
int gLastScrOpcodesRetired[2];
int gLastScrThreadCount[2];
int dword_7DCED9C;
int dword_7DD8DB4;
int rb_execCmdsMS;
int rb_swapMS;

/*
==============
UpdateData
==============
*/
void UpdateData(CG_PerfData *data, int value)
{
	// straight from ida

	int count;
	float v7;
	int v8;
	float v9;

	data->history[data->index % 32] = value;
	count = data->count;
	int v3 = 0;
	data->instant = value;
	data->min = 0x7FFFFFFF;
	data->max = 0;
	data->average = 0.0;
	data->variance = 0.0;
	data->total = 0;

	if (count > 0)
	{
		int index = data->index;

		do
		{
			signed int v5 = index & 0x8000001F;

			if (index < 0)
			{
				v5 = ((v5 - 1) | 0xFFFFFFE0) + 1;

				if (v5 < 0)
				{
					break;
				}
			}

			data->total += data->history[v5];

			if (data->min > data->history[v5])
			{
				data->min = data->history[v5];
			}

			int v6 = data->history[v5];

			if (data->max < v6)
			{
				data->max = v6;
			}

			++v3;
			--index;
		}
		while (v3 < count);
	}

	float v7 = count;
	int v8 = 0;
	float v9 = data->total / count;
	data->average = v9;

	if (count > 0)
	{
		int v10 = data->index;
		do
		{
			signed int v11 = v10 & 0x8000001F;

			if (v10 < 0)
			{
				v11 = ((v11 - 1) | 0xFFFFFFE0) + 1;
				if (v11 < 0)
				{
					break;
				}
			}

			++v8;
			// data->variance = COERCE_FLOAT(COERCE_UNSIGNED_INT(data->history[v11] - v9) & _mask__AbsFloat_) + data->variance;
			--v10;
		}
		while (v8 < data->count);
	}

	float variance = data->variance;
	++data->index;
	data->variance = variance / v7;
}

/*
==============
CG_PerfInit
==============
*/
void CG_PerfInit()
{
	if (!cg_perfInfo.initialized)
	{
		memset(&cg_perfInfo, 0, sizeof(cg_perfInfo));

		cg_perfInfo.frame.count = 32;
		cg_perfInfo.script.count = 10;
		cg_perfInfo.script_devblocks.count = 10;
		cg_perfInfo.cscript.count = 10;
		cg_perfInfo.server.count = 20;
		cg_perfInfo.script_opcodes.count = 10;
		cg_perfInfo.cscript_opcodes.count = 10;
		cg_perfInfo.script_threads.count = 10;
		cg_perfInfo.cscript_threads.count = 10;
		cg_perfInfo.renderExec.count = 32;
		cg_perfInfo.renderSwap.count = 32;
		cg_perfInfo.initialized = 1;
	}
}

/*
==============
CG_PerfUpdate
==============
*/
void CG_PerfUpdate()
{
	CG_PerfInit();

	int v0 = Sys_Milliseconds();
	int v1 = v0 - previousMS;
	previousMS = v0;

	UpdateData(&cg_perfInfo.frame, v1);
	UpdateData(&cg_perfInfo.server, (gRunFrameTicks * msecPerRawTimerTick));
	UpdateData(&cg_perfInfo.script, gLastScrExecuteTime[0]);
	UpdateData(&cg_perfInfo.cscript, dword_7DCED84);
	UpdateData(&cg_perfInfo.script_opcodes, gLastScrOpcodesRetired[0]);
	UpdateData(&cg_perfInfo.script_threads, gLastScrThreadCount[0]);
	UpdateData(&cg_perfInfo.cscript_opcodes, dword_7DCED9C);
	UpdateData(&cg_perfInfo.cscript_threads, dword_7DD8DB4);
	UpdateData(&cg_perfInfo.renderExec, rb_execCmdsMS);
	UpdateData(&cg_perfInfo.renderSwap, rb_swapMS);
}

