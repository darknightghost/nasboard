#! /usr/bin/env python3
# -*- coding: utf-8 -*-

import serial
import os

class DeviceNotFoundError(Exception):
    pass

class NasBoard:
    RED = 0x00
    GREEN = 0x08
    def open(self):
        path_list = self.__get_dev_paths()

        if len(path_list) == 0:
            raise DeviceNotFoundError()

        for p in path_list:
            try:
                self.serial = serial.Serial(port = p,
                        baudrate = 9600,
                        bytesize = serial.EIGHTBITS,
                        parity = serial.PARITY_NONE,
                        stopbits = serial.STOPBITS_ONE,
                        timeout = 5)

                self.serial.open()

                if not self.handshake():
                    self.serial.close()
                    continue

                return

            except serial.SerialException as e:
                if  self.handshake():
                    return

                continue

        raise DeviceNotFoundError()

    def close(self):
        self.serial.close()
    
    def __get_dev_paths(self):
        files = os.listdir("/dev")
        ret = []
        for f in files:
            if "ttyUSB" in f:
                ret.append(os.path.join("/dev", f))

        return ret

    def handshake(self):
        try:
            self.serial.write(b'\x00')

        except serial.SerialTimeoutException:
            return False

        if self.serial.read(1) == b'\xAB':
            return True

        else:
            return False

    def get_ac_stat(self):
        try:
            self.serial.write(b'\x40')

        except serial.SerialTimeoutException:
            raise DeviceNotFoundError()

        result = self.serial.read(1)
        if len(result) == 0:
            raise DeviceNotFoundError()

        if result[0] == 0:
            return False

        elif result[0] == 1:
            return True

        else:
            raise DeviceNotFoundError()

    def clear(self):
        try:
            self.serial.write(b'\x10')

        except serial.SerialTimeoutException:
            raise DeviceNotFoundError()

    def light_on(self, color, index):
        if color not in (self.RED, self.GREEN):
            raise ValueError("Illegal color.")

        if index > 7:
            raise ValueError("Illegal index.")

        cmd = 0x20 | color | index

        try:
            self.serial.write(bytes([cmd]))

        except serial.SerialTimeoutException:
            raise DeviceNotFoundError()

    def light_off(self, index):
        if index > 7:
            raise ValueError("Illegal index.")

        cmd = 0x30 | index

        try:
            self.serial.write(bytes([cmd]))

        except serial.SerialTimeoutException:
            raise DeviceNotFoundError()

