
SCURTA DESCRIERE A APLICATIEI

Aplicatia reprezinta un sistem complet de management pentru o Liga de Baschet.
Aceasta asigura gestiunea si evidenta entitatilor specifice domeniului sportiv:
  - Ierarhia polimorfica Persoana -> Jucator -> Capitan (cu mostenire virtuala,
    clase abstracte, metode pur virtuale si functionalitati specifice).
  - Clasa Antrenor (ce urmareste performanta pe sezoane).
  - Clasa Echipa (lotul de jucatori securizat prin std::unique_ptr, fani, conferinta).
  - Clasa Meci (scorul pe sferturi, logica meciurilor acasa/deplasare).

Functia main() ofera un meniu interactiv CRUD complet, tratat prin blocuri 
try-catch multiple, testarea fenomenului de Stack Unwinding, aplicarea 
sistemului Abstract Factory pentru echipamente si rularea algoritmilor STL.

JUSTIFICAREA ALEGERII CONTAINERELOR STL UTILIZATE 

Toate tablourile alocate dinamic vechi (new[]) au fost eliminate complet, 
fiind inlocuite cu minimum 3 tipuri diferite de containere STL specifice:

A. std::vector
   - Locatii de utilizare: Lotul de jucatori (Echipa::listaJucatori), istoricul
     antrenorilor (Antrenor::victoriiPeSezon), punctajele meciurilor (Meci::punctePeSfert),
     precum si colectiile principale din main (liga si staffLiga).
   - Justificare: Ofera stocare contigua in memorie. Accesul la elemente prin 
     operatorul[] se realizeaza in timp constant O(1), optim pentru parcurgerea 
     si afisarea lotului. Adaugarea prin push_back se face in O(1) amortizat, 
     evitand realocarile manuale costisitoare.

B. std::map
   - Locatie de utilizare: Meniul 9 (gruparea si evidenta echipelor pe conferinte).
   - Justificare: Stocheaza perechi cheie-valoare unice ordonate automat dupa cheie. 
     Structura interna se bazeaza pe un arbore binar echilibrat (Red-Black Tree), 
     ceea ce garanteaza o complexitate de O(log N) pentru operatiile de cautare, 
     inserare si stergere a categoriilor de conferinte.

C. std::set
   - Locatie de utilizare: Meniul 9 (stocarea si sortarea numelor unice ale echipelor).
   - Justificare: Setul garanteaza in mod nativ unicitatea elementelor introduse 
     si le sorteaza automat alfabetic. Complexitatea pentru operatiile de inserare 
     si verificare este O(log N), ideala pentru eliminarea rapida a duplicatelor 
     in momentul procesarii numelor de echipe din intreaga liga.

ALGORITMI STL UTILIZATI

In cadrul functiei main() au fost integrati minimum 5 algoritmi diferiti cu 
expresii lambda pentru operarea colectiilor:
  1. std::sort - Sorteaza descrescator echipele dupa fani.
  2. std::for_each - Parcurge si afiseaza clasamentul popularitatii.
  3. std::count_if - Numara in mod optim echipele apartinand conferintei "Est".
  4. std::any_of - Verifica daca exista vreo echipa cu peste 50.000 de fani.
  5. std::transform - Extrage si converteste numele din lot intr-un set unic.
  6. Idioma erase-remove_if - Elimina din vectorul 'liga' echipele cu 0 fani.

DESIGN PATTERNS IMPLEMENTATE

  - Singleton (Varianta Meyers): Clasa 'Logger', apelata automat de catre constructori 
    si sistemul de exceptii pentru asigurarea unui audit centralizat al aplicatiei.
  - Abstract Factory: Sistemul de generare a echipamentelor sportive (Mingi si Tricouri) 
    organizat pe familii de produse (Est / Vest), integrat prin Dependency Injection 
    in clasa client 'ManagerEchipamente'.
