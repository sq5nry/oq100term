# qo-100term
Software part of the QO-100 satellite terminal.
The first geostationary amateur radio transponder (P4-A) on Es’hail-2 is a joint project by the Qatar Satellite Company (Es’hailSat), the Qatar Amateur Radio Society (QARS) and AMSAT Deutschland (AMSAT-DL). https://amsat-dl.org/eshail-2-amsat-phase-4-a/

![housing](/img/out.jpg)

The whole transverter (terminal) is connected to ICOM-7000 serving as IF on 70cm. PLL is switched between 1966MHz and 51.5(6)MHz for T/R. The latter goes to /2 prescaler end enters LNB PLL ref input as 25.78(3)MHz. A small Arduino controller is connected with ADF board and watches the PTT line.
![interior](/img/in.jpg)

Schematics diagram:
![Schematics diagram](/img/schematics_diagram.png)

Dish feed:
![Schematics diagram](/img/feed.jpg)
