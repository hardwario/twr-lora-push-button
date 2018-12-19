#!/usr/bin/env python3
import sys
import __future__

HEADER_BOOT =  0x00
HEADER_UPDATE = 0x01
HEADER_BUTTON_CLICK = 0x02
HEADER_BUTTON_HOLD  = 0x03

header_lut = {
    HEADER_BOOT: 'BOOT', 
    HEADER_UPDATE: 'UPDATE',
    HEADER_BUTTON_CLICK: 'BUTTON_CLICK',
    HEADER_BUTTON_HOLD: 'BUTTON_HOLD'
}


def decode(data):
    if len(data) != 18:
        raise Exception("Bad data length, 18 characters expected")

    header = int(data[0:2], 16)

    temperature = int(data[6:10], 16) if data[6:10] != 'ffff' else None

    if temperature:
        if temperature > 32768:
            temperature -= 65536
        temperature /= 10.0

    return {
        "header": header_lut[header],
        "voltage": int(data[2:4], 16) / 10.0 if data[2:4] != 'ff' else None,
        "orientation": int(data[4:6], 16),
        "temperature": temperature,
        "click_count": int(data[10:14], 16) if data[20:24] != 'ffff' else None,
        "hold_count": int(data[14:18], 16) if data[24:28] != 'ffff' else None
    }


def pprint(data):
    print('Header :', data['header'])
    print('Voltage :', data['voltage'])
    print('Orientation :', data['orientation'])
    print('Temperature :', data['temperature'])
    print('Click count :', data['click_count'])
    print('Hold count :', data['hold_count'])


if __name__ == '__main__':
    if len(sys.argv) != 2 or sys.argv[1] in ('help', '-h', '--help'):
        print("usage: python3 decode.py [data]")
        print("example: python3 decode.py 021a0200d100010000")
        exit(1)

    data = decode(sys.argv[1])
    pprint(data)
