from coap import coap
import time

c = coap.coap()
print("initializing")

address1 = 'coap://[bbbb::12:4b00:430:531c]'
address2 = 'coap://[bbbb::12:4b00:430:53fd]'

#resources1 = c.GET(address1 + '/.well-known/core')
#print(''.join([chr(b) for b in resources1]))
resources2 = c.GET(address2 + '/.well-known/core')
print(''.join([chr(b) for b in resources2]))

print("ready")

def toggle_531c():
    c.PUT(address1 + '/g',payload=[ord('2')],)

def toggle_53fd():
    c.PUT(address2 + '/g',payload=[ord('2')],)

def switchNTimes(n):
    for i in range(n):
        #toggle_531c()
        #time.sleep(1)
        toggle_53fd()
        time.sleep(1)
