#include <lib/dvb/eit.h>
#include <lib/dvb/specs.h>
#include <lib/base/eerror.h>
#include <lib/service/event.h>
#ifdef __sh__
#include <lib/dvb/epgcache.h>
#endif

void eDVBServiceEITHandler::EITready(int error)
{
	if (!error)
	{
		ePtr<eTable<EventInformationSection> > ptr;
		if (!m_EIT.getCurrent(ptr))
		{
			int a = 0;
			for (std::vector<EventInformationSection*>::const_iterator i = ptr->getSections().begin();
				i != ptr->getSections().end(); ++i)
			{
				const EventInformationSection *eit = *i;
				for (EventConstIterator ev = eit->getEvents()->begin(); ev != eit->getEvents()->end(); ++ev)
				{
#ifdef __sh__
					if(!eEPGCache::getInstance()->CheckEPGBlock (-1, eit->getTransportStreamId (), eit->getOriginalNetworkId (), 1))
					{
						ePtr<eServiceEvent> evt = new eServiceEvent();
						evt->parseFrom(*ev,(eit->getTransportStreamId()<<16)|eit->getOriginalNetworkId());
						if (!a)
							m_event_now = evt;
						else
							m_event_next = evt;
					}
#else
					ePtr<eServiceEvent> evt = new eServiceEvent();
					evt->parseFrom(*ev,(eit->getTransportStreamId()<<16)|eit->getOriginalNetworkId());
					if (!a)
						m_event_now = evt;
					else
						m_event_next = evt;
#endif
					++a;
				}
			}
		}
	}

	m_eit_changed();
}

void eDVBServiceEITHandler::inject(ePtr<eServiceEvent> &event, int nownext)
{
	if (nownext)
		m_event_next = event;
	else
		m_event_now = event;
	m_eit_changed();
}

eDVBServiceEITHandler::eDVBServiceEITHandler()
{
	CONNECT(m_EIT.tableReady, eDVBServiceEITHandler::EITready);
}

void eDVBServiceEITHandler::start(iDVBDemux *demux, int sid)
{
	m_EIT.begin(eApp, eDVBEITSpec(sid), demux);
}

void eDVBServiceEITHandler::startOther(iDVBDemux *demux, int sid)
{
	m_EIT.begin(eApp, eDVBEITSpecOther(sid), demux);
}

RESULT eDVBServiceEITHandler::getEvent(ePtr<eServiceEvent> &event, int nownext)
{
	event = nownext ? m_event_next : m_event_now;
	if (!event)
		return -1;
	return 0;
}
