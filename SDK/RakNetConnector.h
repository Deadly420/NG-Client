#pragma once

class RakNetConnector {
private:
	char pad_0x8[0x420];  // 0x8
public:
	TextHolder numericalIp;  // 0x428
	TextHolder serverIp;     // 0x448
	uint32_t serverPort;     // 0x468

	virtual void Destructor();
	virtual std::vector<TextHolder*> getLocalIps(void);
	virtual TextHolder *getLocalIp(void);
	virtual uint16_t getPort(void);
	virtual __int64 getRefinedLocalIps(void);
	virtual __int64* getConnectedGameInfo(void);
	virtual void setupNatPunch(bool connectToClient);
	virtual __int64 *getNatPunchInfo(void);
	virtual void startNatPunchingClient(std::string const &, short);
	virtual void addConnectionStateListener(__int64*);
	virtual void removeConnectionStateListener(__int64*);
	virtual bool isIPv4Supported(void);
	virtual bool isIPv6Supported(void);
	virtual uint16_t getIPv4Port(void);
	virtual uint16_t getIPv6Port(void);
	virtual void host(__int64 const definition);
	virtual void connect(__int64 const &, __int64 const &);
	virtual void disconnect(void);
	virtual void tick(void);
	virtual void runEvents(void);
	virtual bool isServer(void);
	virtual bool isConnected(class NetworkIdentifier const &);
	virtual __int64 closeNetworkConnection(NetworkIdentifier const &);
	virtual __int64* getNetworkIdentifier(void);
	virtual __int64* getPeer(void);
	virtual __int64* getPeerConst(void);
	virtual void _onDisable(void);
	virtual void _onEnable(void);

public:
	bool isonaServer() { return !(serverIp.textLength == 0); }

};