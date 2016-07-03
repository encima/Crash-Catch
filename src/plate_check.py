import requests
import string
import time
from bs4 import BeautifulSoup

url = "https://www.vehiclecheck.co.uk/?SC=132&vrm={}"
plates = ["H{}54 KPO","H{}54 KPD","H{}54 KFO","H{}54 KFD","H{}64 KPO","H{}64 KPD","H{}64 KFO","H{}64 KFD"]


matches = []
letters = string.letters[:26]
f = open('../data/matches.txt', 'w')
for plate in plates:
    for a in letters:
        for b in letters:
            for c in letters:
                for d in letters:
                    for e in letters:
                        p = plate.format(a,b,c,d,e).lower()
                        print(p)
                        r = requests.get(url.format(p))
                        print(r.status_code)
                        if r.status_codes_code == 200 and "BMW" in r.text:
                            print(p)
                            soup = BeautifulSoup(r.text, 'html.parser')
                            match = soup.find(id="searchResult").h3
                            print(match)
                            matches.append({'plate':p, 'car': match})
                            f.writelines(match)
                        time.sleep(2)
f.close()
