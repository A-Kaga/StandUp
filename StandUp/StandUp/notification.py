import requests

def notification():
    url = 'https://maker.ifttt.com/trigger/StandUp/with/key/b1-1FsKc9XxI48veEVHCoQ'
    requests.post(url)

print(notification())