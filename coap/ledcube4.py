import sys
import datetime
import serial

from twisted.internet import defer
from twisted.internet.protocol import DatagramProtocol
from twisted.internet import reactor
from twisted.python import log

import txthings.resource as resource
import txthings.coap as coap

class LedCube:
    def __init__(self, device):
        self.conn = serial.Serial(device, 9600)

    def sendCommand(self, cmd):
        self.conn.write(cmd + '\n')
        s = self.conn.readline()
        return s == "\r\n"

class LedCubeResource (resource.CoAPResource):
    def __init__(self, ledCube):
        resource.CoAPResource.__init__(self)
        self.ledCube = ledCube
        self.visible = True
        self.addParam(resource.LinkParam("title", "LED Cube resource"))

    def render_GET(self, request):
        response = coap.Message(code=coap.CONTENT, payload=
                                    "usage: PUT loop|clap|visual|blend|fill|scanner|randomize|"+
                                    "extend_from_corner|snake|up_down|image|fan|visualize")
        return defer.succeed(response)
        
    def render_PUT(self, request):
        code = coap.CHANGED if self.ledCube.sendCommand(request.payload) else coap.BAD_REQUEST
        response = coap.Message(code=code)
        return defer.succeed(response)

class CoreResource(resource.CoAPResource):
    def __init__(self, root):
        resource.CoAPResource.__init__(self)
        self.root = root

    def render_GET(self, request):
        data = []
        self.root.generateResourceList(data, "")
        payload = ",".join(data)
        print payload
        response = coap.Message(code=coap.CONTENT, payload=payload)
        response.opt.content_format = coap.media_types_rev['application/link-format']
        return defer.succeed(response)

assert len(sys.argv) == 2
log.startLogging(sys.stdout)
root = resource.CoAPResource()
well_known = resource.CoAPResource()
root.putChild('.well-known', well_known)
well_known.putChild('core', CoreResource(root))
root.putChild('led-cube', LedCubeResource(LedCube(sys.argv[1])))

endpoint = resource.Endpoint(root)
reactor.listenUDP(coap.COAP_PORT, coap.Coap(endpoint), interface="::")
reactor.run()
