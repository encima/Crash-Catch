#HSLIDE

## TO CATCH A PREDATOR
### Or: How I Learned That People Suck

---

### [Chris Gwilliams](https:twitter.com/encima27)

#HSLIDE 

### Some Background

#### I bought a house out of sheer desperation 
#### The similiarites to [The Money Pit](http://www.imdb.com/title/tt0091541/) are striking
#### Strange things happened to my car shortly after moving in, so I bought some CCTV. Problem solved?

#HSLIDE

### Problem **NOT** Solved

* Rear Window Smashed
* Creepy child's scooter rolls out of the dark towards my (then) brand new car
* Wing mirrors cracked
* Some dude reverses into me and drives away

#HSLIDE 

### You Will Need:

* A damaged car <!-- .element: class="fragment" -->
* A poor experience with the Police <!-- .element: class="fragment" -->
* A lonely life <!-- .element: class="fragment" -->
* CCTV so grainy that people believe it is a clip from the 1950s <!-- .element: class="fragment" -->
* OpenCV knowledge <!-- .element: class="fragment" -->
* Python fun skills <!-- .element: class="fragment" -->

#HSLIDE 

#### Step One: Extract Your Video

<p>Your CCTV box is likely a large black hunk of Chinese excellence. Navigate the menus and find that extracting is difficult.</p>
<p>Film it on your phone and realise that you are filming at 4K a video being output to 1024*768 monitor</p>
<p>Navigate harder and see that you must first find the video name and then plug in a FAT USB. Do that and slap it into your PC with childish glee</p>

**Result?** Watch repeatedly and show people over and over 

#HSLIDE

#### Step Dos: Crowdsource

<p>Slap the video on Twitter and see who helps</p>
<blockquote class="twitter-tweet" data-lang="en"><p lang="en" dir="ltr">If anyone can figure out the number plate of this douche, I will get you all the beers. <a href="https://t.co/siykOxg78K">pic.twitter.com/siykOxg78K</a></p>&mdash; Chris Gwilliams (@encima27) <a href="https://twitter.com/encima27/status/741157774386724864">June 10, 2016</a></blockquote>
<script async src="//platform.twitter.com/widgets.js" charset="utf-8"></script>

**Result?** Some designers photoshop it but mostly people say no

#HSLIDE

### Step the Third: Load Into OpenCV 

* Read video in and play frame-by-frame 
* Invert video and apply smoothing 
* Allow ROI to be selected

![enhance](http://i.giphy.com/10nMEclFWTPCp2.gif)

**Result?** Watch frames obsessively. Grey hairs.

#HSLIDE 

### Step 4: Squint? Guess? Maybe?

* Create a list of possible letters
* Some are clear but 2 chars are NOT
* Python Time!
    1. Create a list of formatted strings
    2. Find an API to check number plates

```python 
plates = ["H{}54 KPO","H{}54 KPD","H{}54 KFO","H{}54 KFD",
"H{}64 KPO","H{}64 KPD","H{}64 KFO","H{}64 KFD"]
```

**Result?** Scream 'GOT YOU'. Make dog bark. 

#HSLIDE 

### Step E: Find a Number Plate API

1. [DVLA](https://vehicleenquiry.service.gov.uk/) - Post request, NO API, need to know make Open data government...
2. [DVLA Search](https://dvlasearch.co.uk/) - API, but costs
3. [AutoTrader Vehicle Check](https://www.vehiclecheck.co.uk/?SC=132&vrm=<PLATE>) - GET request

**Result?** Realise the number of browser tabs open may be more than the litres of lucozade I have consumed

#HSLIDE 

### Step Sechs: Requests

```python 
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
```

**Result?** Scream when computer beeps. Hope no more matches exist. They do not.

#HSLIDE 

### The Eighth Step: Profit

* We have a match!
* Tell Police  
    1. Case closed (wait, what?)
    2. Case opened, person found and charged monies 6 months later <!-- .element: class="fragment" -->
    3. Thank you, Police <!-- .element: class="fragment" -->
* Tell Insurance
    * Owned by rental car company :(
    * Admit fault and buy me a new door!
* Sleep soundly and coast off success for 6 months 

# HSLIDE 

### Real Talk: What Have We Learnt?

* These are skills that can be Learnt
* Currently, Police are too short staffed and insurance do not have this (despite claims they do)
* Crude solution in <200 LOC 
* GET CCTV 
* How would I be interesting if I had not done this?



