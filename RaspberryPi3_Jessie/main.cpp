#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include "TL_INetSyphonSDK.h"
#include <bcm_host.h>	// for dispmanx schlop


TL_INetSyphonSDK*	gManager = 0;

TL_INetSyphonSDK_BonjourItem	gConnectedHost;
char gConnectServerName[256];
int	 gConnectServerPort;
char gBindToDeviceName[256];


void	OnNotify_ChangedServer( std::vector<TL_INetSyphonSDK_BonjourItem> servers )
{
	int i, num;

	num = servers.size();
	for (i=0;i<num;i++)
	{
		TL_INetSyphonSDK_BonjourItem	item = servers[i];
		if ( item.m_Name == gConnectedHost.m_Name ) return;
	}
	if ( num > 0 )
	{
		int isel = 0;
		for (i=0;i<num;i++)
		{
			TL_INetSyphonSDK_BonjourItem	item = servers[i];
			if ( item.m_Name == gConnectServerName )
			{
				isel = i;
				break;
			}
		}
		TL_INetSyphonSDK_BonjourItem	item = servers[isel];

		gManager->ConnectToTCPSyphonServerByName( item.m_Name.c_str() );
		gConnectedHost = item;
	}
	else
	{
		gConnectedHost.m_Name = "";
	}
}


void	analysis_Commandline( int argc, char **argv )
{
    int opt;

    while((opt = getopt(argc, argv, "lp:c:s:d:b:")) != -1){
        switch(opt){
            case 'l':
            	strcpy( gConnectServerName, "#_dummy" );
            	break;
            case 'c':
            	strcpy( gConnectServerName, optarg );
            	break;
            case 'p':
            	gConnectServerPort = atoi( optarg );
            	break;

            case 's':
            	{
            		float l,t, r,b;
            		l=0;
            		r=1;
            		t=0;
            		b=1;
            		sscanf( optarg, "%f,%f,%f,%f", &l, &t, &r, &b );
            		gTexCoords[0*2+0] = l;
            		gTexCoords[4*2+0] = l;
            		gTexCoords[5*2+0] = l;
            		gTexCoords[1*2+0] = r;
            		gTexCoords[2*2+0] = r;
            		gTexCoords[3*2+0] = r;

            		gTexCoords[0*2+1] = 1.0-b;
            		gTexCoords[1*2+1] = 1.0-b;
            		gTexCoords[5*2+1] = 1.0-b;
            		gTexCoords[2*2+1] = 1.0-t;
            		gTexCoords[3*2+1] = 1.0-t;
            		gTexCoords[4*2+1] = 1.0-t;
            	}
            	break;
            case 'd':
            	{
            		int x,y,w,h;
            		sscanf( optarg, "%d,%d,%d,%d", &x, &y, &w, &h );
            		gRequestVerticesFullScreen = true;
            		gRequestVerticesFullScreenX = x;
            		gRequestVerticesFullScreenY = y;
            		gRequestVerticesFullScreenW = w;
            		gRequestVerticesFullScreenH = h;
							}
							break;
						case 'b':
            	strcpy( gBindToDeviceName, optarg );
            	break;

            case '?':
                printf("Unknown or required argument option -%c\n", optopt);
                printf("Usage: COMMAND [-l -c server(IP address) -p port -s source_area -d destination_area] -b devicename ...\n");
                printf("l: display servers\n");
                printf("source_area: left(0),top(0),right(1),bottom(1)\n");
                printf("destination_area: x(0),y(0),width(1920),height(1080)\n");
								printf("b: Bind to device, Ex. eth0, wlan0, eth1 \n");
                exit(0);
                break;
        }
    }
    printf( "\n" );
}


int main(int argc, char **argv)
{
	gBindToDeviceName[0] = 0;
	gConnectServerName[0] = 0;
	gConnectServerPort = 7778;

	printf( "\nTCPSClient publicbeta10 Copyright(C) 2015-2017 Nozomu Miura. All rights reserved.\n\n" );

	analysis_Commandline( argc, argv );

	gManager = TL_INetSyphonSDK::CreateInstance();

	if ( gManager->Initialization( OnNotify_ChangedServer ) )
	{
		return 1;
	}

	if ( gBindToDeviceName[0] != 0 )
	{
		gManager->SetBindToDevice( gBindToDeviceName );
	}

	if ( gConnectServerName[0] != 0 )
	{
		gManager->ConnectTo( gConnectServerName, gConnectServerPort );
	}
	else
	{
		//Starts Bonjour.
		gManager->StartClient();
	}

	int reconnectCounter = 0;
	while ( 1 )
	{
		int ret;

		ret = gManager->Render();
		if ( 1 == ret )
		{
			if ( gConnectServerName[0] != 0 )
			{
				gManager->DisconnectToTCPSyphonServer();

				gManager->ConnectTo( gConnectServerName, gConnectServerPort );
			}
			else
			{
				++reconnectCounter;
				if ( reconnectCounter > 60 * 1 )
				{
					//retry connection
					gManager->ConnectToTCPSyphonServerByName( gConnectedHost.m_Name.c_str() );

					reconnectCounter = 0;
				}
			}
		}
		else
			reconnectCounter = 0;
	}
	gManager->DisconnectToTCPSyphonServer();
	gManager->StopClient();

	delete gManager;
	gManager = 0;

	return	0;
}
