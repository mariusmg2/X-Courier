# X-Courier

X-Courier-alpha-0.1

Known bugs:
- When in DB are more clients with the same name (or the same client sends multiple packages), status system will show only the 
first one.
- There is no class that will cover the transport type (slow/medium/fast). So this option is null, it will not affect the shipping 
price or delivery date/time.

Task:

# Sistem de management pentru o firma de curierat rapid

Se cere sa se proiecteze un sistem de management pentru o firma de curierat 
rapid care sa indeplineasca urmatoarele cerinte:

a] Firma are mai multe sedii în diverse orase şi o lista de rute şi 
tipuri de transporturi disponibile intre orase, impreuna cu orarele lor.

b] Un client se prezinta la un sediu al firmei avand pachetul pe care 
doreste sa-l trimita şi completeaza un formular în care sunt trecute datele lui 
de contact, orasul de destinatie si datele de contact ale destinatarului. La 
cestea functionarul mai adauga greutatea coletului, daca coletul face parte din 
una din urmatoarele categorii speciale: fragil/pretios/periculos. Pentru 
coletele pretioase şi pentru cele periculoase se va face trasnportul doar daca 
se gasesc conditii corespunzatoare de transport.

c]  Odata datele introduse în sistem, acesta va cauta o ruta cat mai 
rapida, care este posibil sa fie alcatuita din mai multe trasee individuale, în 
asa fel incat sa fie respectate conditiile de transport şi va afisa timpul 
estimat parcurgerii rutei şi distanta.

d] Pretul se calculeaza în functie de distanta rutei, greutatea pachetului 
şi conditiile de transport necesare.

e] Pretul calculat şi timpul estimat necesar sunt prezentate clientului 
pentru ca acesta sa le aprobe sau nu. Daca transportul este aprobat de catre 
client, atunci clientul va plati transportul prin carte de credit sau casch. 
Coletul este preluat de functionar, fiind-ui asignat un cod specific şi 
inregistrat cu statusul „în tranzit direct”.

f] Odata ce pachetul a ajuns în orasul de destinatie, i se va schimba 
statusul în „în asteptare destinatar” si se va contacta destinatarul. Daca 
acesta raspunde, este anuntat ca a primit coletul şi este invitat sa-l ridice. 
Daca timp de trei zile nu se poate contacta destinatarul, se va apela 
expeditorul şi va fi intrebat daca sa se prelungeasca timpul de asteptare a 
coletului sau acesta sa fie returnat. Pentru fiecare zi de asteptare 
suplimentara exista o taxa suplimentara de magazie, calculata în functie de 
greutatea pachetului şi de conditiile speciale cerute de acesta.

g] În cazul în care se opteaza pentru returnarea pachetului, statusul 
acestuia se schimb în „în tranzit retur” şi va fi trimis inapoi catre orasul de 
expeditie. Daca nu se mai poate contacta nici expeditorul, pachetul va mai fi 
tinut inca o saptamana, zile pentru care va trebui sa fie platita la ridicare 
taxa de magazie, iar dupa aceste zile va inta în posesia firmei de curierat.

h] Soferii de pe un transport au obligatia ca în fiecare oras de tranzit 
sa-şi anunate pozitia, în asa fel incat expeditorul şi destinatarul sa stie cat 
timp a mai ramas pana la livrare.

