# 🌌 TDT4102 Gravitational Simulation – Final Project

Dette prosjektet simulerer et enkelt solsystem med en sol, en planet og en måne i bane. Programmet bruker en kombinasjon av 2D- og 3D-grafikk gjennom NTNU sitt AnimationWindow-bibliotek. Simulasjonen er fysikkbasert og benytter Newtons gravitasjonslov til å styre interaksjonen mellom objektene.

## 🔧 Struktur og viktige filer

Prosjektet består av tre hovedkomponenter implementert i hver sin headerfil:

### ball.h

Denne klassen representerer en 2D-ball brukt i de enklere testene (case 1–4). Den implementerer metoder som update() for å oppdatere posisjon med fart, draw() for å tegne ballen, og apply_gravity_from() for å simulere gravitasjon fra en annen ball. Den brukes hovedsakelig for å eksperimentere med bevegelse og kollisjoner.

### 3d.h

Her defineres strukturer og funksjoner for 3D-visualisering. Vec3 representerer en 3D-vektor og har overlastede operatorer som +, -, og * for enkel vektorregning. project() funksjonen konverterer et 3D-punkt til et 2D-punkt på skjermen med perspektivprojeksjon. draw_mesh_filled() tegner fylte trekantmesh med enkel lyssetting via dot-produkt mellom trekantens normal og en lyssretning.

### celestial_body.h

Dette er den objektorienterte ryggraden i prosjektet. CelestialBody er en abstrakt baseklasse som representerer himmellegemer. Den har virtuelle funksjoner som update_position(), apply_gravity_from(), og type(), slik at arvede klasser (Sun, Planet, Moon) kan implementere forskjellig oppførsel. F.eks. har Sun ingen bevegelse, Planet kan kaste unntak hvis den forlater systemet, og Moon beveger seg langsommere.

### 🌍 Case 8 – Final Demo

Hoveddemoen (case 8) viser en realistisk sol og planet i bane basert på fysikk, mens månen følger en hardkodet bane rundt planeten. Trajektorier vises ved hjelp av vektorer, og 3D-illusjon oppnås med shading. Farger og masser bestemmer visuell oppførsel.

### 🎓 Oppsummering

Prosjektet viser:
	•	Arv og polymorfi
	•	Vektorregning og 3D-transformasjon
	•	Bruk av Newtons gravitasjonslov
	•	Bruk av grafisk brukergrensesnitt
	•	Unntakshåndtering i gravitasjonsberegning

Simulasjonen er både visuell og fysisk informativ, og prosjektet er bygget opp modulært med tydelig klasseansvar.