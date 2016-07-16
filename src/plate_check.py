import requests
import string
import time
from bs4 import BeautifulSoup
import config


matches = []
letters = string.letters[:26]
f = open('../data/matches.txt', 'w')
for plate in config.plates:
    for a in letters:
        for b in letters:
			p = plate.format(a,b).lower()
			print(p)
			r = requests.get(config.url.format(p))
			if r.status_code == 200 and "BMW" in r.text:
				soup = BeautifulSoup(r.text, 'html.parser')
				match = soup.find(id="searchResult").h3
				print(match)
				matches.append({'plate':p, 'car': match})
				f.writelines(match)
			time.sleep(2)
f.close()
