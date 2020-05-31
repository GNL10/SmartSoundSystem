from firebase import firebase
from time import sleep
import os
import signal
import sys

def update_vol_bal(balance, volume):
    if balance == 'left':
        os.popen('amixer sset Master 0%,' + str(volume) + '%')
    elif balance == 'right':
        os.popen('amixer sset Master ' + str(volume) + '%,0%')

# when ctrl+c is pressed kill the tmux session before exiting
def signal_handler(sig, frame):
    os.popen('tmux kill-session -t SmartSoundSystem')
    sys.exit(0)

#connecting to the firebase
firebase = firebase.FirebaseApplication("https://smart-sound-system.firebaseio.com/", None)

#open spotify
os.popen('tmux new-session -s SmartSoundSystem -d -n spotify tizonia --spotify-playlist "New"')
signal.signal(signal.SIGINT, signal_handler)
on = 1
volume = 100
balance = 'left'

while 1:
    result = firebase.get('/Instructions', '')
    if result != None:
        #processing all available Instructions
        for key, inst in result.items():  #for each command
            firebase.delete('/Instructions', key)
            print(inst)
            if inst == 'ONOFF':
                if on == 1:
                    os.popen('tmux kill-session -t SmartSoundSystem')
                    on=0
                else:
                    os.popen('tmux new-session -s SmartSoundSystem -d -n spotify tizonia --spotify-playlist "New"')
                    on=1

            elif inst == 'NEXT':  	#send n
                os.popen('tmux send-keys -t spotify "n^M"')
                update_vol_bal(balance, volume)

            elif inst == 'PREV':	#send p
                os.popen('tmux send-keys -t spotify "p^M"')
                update_vol_bal(balance, volume)

            elif inst == 'PLAY':	#send space
                os.popen('tmux send-keys -t spotify " ^M"')

            elif inst == 'UP':  	#send +
                if volume <= 90:
                    volume = volume + 10
                update_vol_bal(balance, volume)

            elif inst == 'DOWN':	#send -
                if volume >= 10:
                    volume = volume - 10
                update_vol_bal(balance, volume)

            elif inst == 'LEFT':	#change balance to left speaker
                balance = 'left'
                update_vol_bal(balance, volume)

            elif inst == 'RIGHT':	#change balance to right speaker
                balance = 'right'
                update_vol_bal(balance, volume)
    sleep(2)
