#include "types.h"

/*
==============
dwQoSMultiProbeListener::complete
==============
*/
/*LocalTaskState dwQoSMultiProbeListener::complete(dwQoSMultiProbeListener *notthis)
{
	UNIMPLEMENTED(__FUNCTION__);
	LocalTaskState tmp;
	return tmp;
}*/

/*
==============
dwClearQoSProbes
==============
*/
void dwClearQoSProbes()
{
	if (g_dwNetStatus == DW_NET_STARTED_ONLINE)
	{
		bdQoSProbe *QoSProbe = dwGetQoSProbe();
		if (QoSProbe)
		{
			bdQoSProbe::cancelProbes(QoSProbe);
		}
	}
}

/*
==============
dwQoSMultiProbeListener::onQoSProbeFail
==============
*/
/*void dwQoSMultiProbeListener::onQoSProbeFail(dwQoSMultiProbeListener *notthis, bdReference<bdCommonAddr> addr)
{
	UNIMPLEMENTED(__FUNCTION__);
}*/

/*
==============
dwQoSMultiProbeListener::clean
==============
*/
/*void dwQoSMultiProbeListener::clean(dwQoSMultiProbeListener *notthis)
{
	UNIMPLEMENTED(__FUNCTION__);
}*/

/*
==============
dwQoSMultiProbeListener::dwQoSMultiProbeListener
==============
*/
/*void dwQoSMultiProbeListener::dwQoSMultiProbeListener(dwQoSMultiProbeListener *notthis)
{
	UNIMPLEMENTED(__FUNCTION__);
}*/

/*
==============
dwQoSMultiProbeListener::addProbe
==============
*/
/*void dwQoSMultiProbeListener::addProbe(dwQoSMultiProbeListener *notthis, const bdQoSRemoteAddr addr)
{
	UNIMPLEMENTED(__FUNCTION__);
}*/

/*
==============
dwQoSMultiProbeListener::onQoSProbeSuccess
==============
*/
/*void dwQoSMultiProbeListener::onQoSProbeSuccess(dwQoSMultiProbeListener *notthis, const bdQoSProbeInfo *info)
{
	UNIMPLEMENTED(__FUNCTION__);
}*/

/*
==============
dwStartQoSProbes
==============
*/
void dwStartQoSProbes(dwQoSMultiProbeListener *listener, const unsigned int numProbes, XSESSION_INFO *xenonsInfo)
{
	UNIMPLEMENTED(__FUNCTION__);
}

