import pyttsx
import serial
import io
import math
import numpy
import pyaudio


class telem:
    def __init__(self, port):
        self.ser=serial.Serial(port, baudrate=115200)
        self.altitude=0
        self.voltage='0.0'
        self.velocity=0
        self.timestamp=0
    def update(self):
        dataLine=readline(self.ser)
        try:
            splitdata = dataLine.split(',')
            newAlt = int(splitdata[0])
            diff=(float(splitdata[2])-self.timestamp)/100000
            self.velocity=int(float((newAlt-self.altitude))/diff)
            self.altitude=int(splitdata[0])
            self.voltage = (splitdata[1])
            self.timestamp=int(splitdata[2])

        except:
            newAlt=0
        self.ser.flushInput()
        #clear any backlog


def sine(frequency, length, rate):
    length = int(length * rate)
    factor = (float(frequency/10) * (math.pi * 2) / rate)*10
    #factor = (float(frequency*length) * (math.pi * 2) / rate)/length
    return numpy.sin(numpy.arange(length) * factor)


def play_tone(stream, frequency=440, length=0.15, rate=44100, amplitude= 0.25):
    chunks = []
    chunks.append(sine(frequency, length, rate))
    chunk = numpy.concatenate(chunks) * amplitude
    stream.write(chunk.astype(numpy.float32).tostring())
    #stream.write(chunk.astype(numpy.float32).tostring())


def readline(a_serial, eol=b'\r'):
    leneol = len(eol)
    line = bytearray()
    while True:
        c = a_serial.read(1)
        if c:
            line += c
            if line[-leneol:] == eol:
                break
        else:
            break
    return bytes(line)

if __name__ == '__main__':
    p=pyaudio.PyAudio()
    stream = p.open(format=pyaudio.paFloat32,
                    channels=1, rate=44100, output=1)

    vario = telem('COM6')
    engine = pyttsx.init()
    count = 0

    while True:
        count+=1
        #text=raw_input('Type stuff')
        velocity=vario.velocity
        play_tone(stream, 440+1*velocity, length=0.1)
        vario.update()
        voltage=vario.voltage
        altitude=vario.altitude-25

        # altitude = (altitude/10)*10
        # if altitude>100:
        #  altitude=((altitude/100)*100)
        print "Velocity "+str(vario.velocity)+" Altitude "+str(altitude)+" "+str(vario.timestamp)
        # if (count%5==1):
            #engine.say(altitude)
            # if (count%5==1):
            #     engine.say(voltage+"Volts")
        #engine.runAndWait()