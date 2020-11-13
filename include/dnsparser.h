// Interface definitions for DNS parser

#ifndef _NM_DNS_H_
#define _NM_DNS_H_

#include <string>
#include <memory>

#ifdef WIN32
#include <Ws2tcpip.h>   // in_addr
#else // WIN32
#include <netinet/in.h> // in_addr
#endif // WIN32

/**
 * Implement this interface and pass to DnsParserNew() to
 * receive DNS response records.
 */
class DnsParserListener
{
public:
  /**
   * @param name Domain name requested.
   * @param addr Binary IPV4 or IPV6 address in network order.
   */
  virtual void onDnsRec(std::string name, in_addr addr) = 0;
  virtual void onDnsRec(std::string name, in6_addr addr) = 0;
  virtual void onDnsRec(std::string name, std::string cname) = 0;
};

class DnsParser
{
public:
  /**
   * parse
   * When response records are discovered, DnsParserListener.onDnsRec()
   * callback is called.
   * @param payload Pointer to first byte of (UDP) payload for DNS datagram.
   * @param payloadLen Length in bytes of payload.
   */
  virtual int parse(const char *payload, int payloadLen)=0;

  virtual ~DnsParser() {};
};

/**
 * Create a return a new instance of DnsParser and register listener.
 *
 * @param listener       For callbacks
 */
std::unique_ptr<DnsParser> DnsParserNew(DnsParserListener *listener);

#endif // _NM_DNS_H_
