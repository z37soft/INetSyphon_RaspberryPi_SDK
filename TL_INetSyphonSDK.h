#ifndef TL_INETSYPHONSDK_H
#define TL_INETSYPHONSDK_H

#include <vector>
#include <string>

//Server information
class	TL_INetSyphonSDK_BonjourItem
{
public:
    //Host name
	std::string				m_Name;
    //IP Address
	std::string				m_Address;
    //Network port
	int						m_Port;
};


class	TL_INetTCPSyphonSDK_Client;

//Function pointer for callback when a server is added or removed.
typedef void (*TL_INetSyphonSDK_OnNotify_ChangedServer)( std::vector<TL_INetSyphonSDK_BonjourItem> servers );


//main class
class	TL_INetSyphonSDK
{
protected:
	TL_INetTCPSyphonSDK_Client*                 m_Client;
    
	TL_INetSyphonSDK_OnNotify_ChangedServer		m_OnNotify;
	
	TL_INetSyphonSDK();

public:
	static	TL_INetSyphonSDK*	CreateInstance();
	virtual	~TL_INetSyphonSDK();
	
	virtual	void	OnNotify_ChangedServer( std::vector<TL_INetSyphonSDK_BonjourItem> servers );

public:
    //Initialization
	int		Initialization( TL_INetSyphonSDK_OnNotify_ChangedServer notify );
	
    //Start bonjour searching
	int		StartClient();
    //Stop bonjour searching
	void	StopClient();

    //Disconnect
	void	DisconnectToTCPSyphonServer();
    //Connect
	int 	ConnectTo( const char* address, int port );
	int		ConnectToTCPSyphonServerAtIndex( int index );
	int		ConnectToTCPSyphonServerByName( const char* name );

    //return connected TCPSyphon server name
	std::string	GetConnectedTCPSyphonServerName();

    //show to screen ( put it on your render thread )
	int		Render();
};

extern	float gTexCoords[12];
extern	float gVerticesFullScreen[12];

#endif
