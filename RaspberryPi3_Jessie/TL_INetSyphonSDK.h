#ifndef TL_INETSYPHONSDK_H
#define TL_INETSYPHONSDK_H

#include <vector>
#include <string>
#include <unistd.h>
#include <stdint.h>

class	TL_INetSyphonSDK_BonjourItem
{
public:
	std::string				m_Name;
	std::string				m_Address;
	int						m_Port;
};


class	TL_INetTCPSyphonSDK_Client;

typedef void (*TL_INetSyphonSDK_OnNotify_ChangedServer)( std::vector<TL_INetSyphonSDK_BonjourItem> servers );

class	TL_INetSyphonSDK
{
protected:
	TL_INetTCPSyphonSDK_Client*		m_Client;
	TL_INetSyphonSDK_OnNotify_ChangedServer		m_OnNotify;
	
	TL_INetSyphonSDK();

public:
	static	TL_INetSyphonSDK*	CreateInstance();
	virtual	~TL_INetSyphonSDK();
	
	virtual	void	OnNotify_ChangedServer( std::vector<TL_INetSyphonSDK_BonjourItem> servers );

public:
	int		Initialization( TL_INetSyphonSDK_OnNotify_ChangedServer notify );
	
	int		StartClient();
	void	StopClient();

	void	DisconnectToTCPSyphonServer();
	int 	ConnectTo( const char* address, int port );
	int		ConnectToTCPSyphonServerAtIndex( int index );
	int		ConnectToTCPSyphonServerByName( const char* name );

	std::string	GetConnectedTCPSyphonServerName();

	int		Render();
	int		MemoryRender( uint32_t line, uint32_t numLEDs, uint8_t* pixels );
};

extern	float gTexCoords[12];
extern	float gVerticesFullScreen[12];
extern  bool  gRequestVerticesFullScreen;
extern  int   gRequestVerticesFullScreenX, gRequestVerticesFullScreenY, gRequestVerticesFullScreenW, gRequestVerticesFullScreenH;

#endif
