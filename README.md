# Projet ROB3: Rami, Yannis, Vasilis

## **LineaScribe Robot**

### **Informations**

#### Membres

TOBBAL Yannis :	tobbalya@gmail.com

ARIDI Rami :	rami.aridi@etu.sorbonne-universite.fr

SKARLEAS Vasilis :	vasileios.skarleas@etu.sorbonne-universite.fr

#### Cursus

Polytech 3eme année | Spécialité: Robotique

#### Délais

Début: 14/02/24 | Fin: 23/05/24

### **But, objectifs et contexte**

#### But

Le but est de créer un robot capable de dessiner différentes formes sur une feuille de papier. Il doit pouvoir réaliser des formes préprogrammée ainsi qu'être contrôlé manuellement.

Le robot est fixé sur un support carré horizontal comportant une zone de dessin de 10\*10 cm. Il y a 2 exercice qu'il doit réussir. En outre, le robot faut être capable de repondre au cahier des charges disponible <span style="text-decoration: underline;">[ici](https://wiki.fablab.sorbonne-universite.fr/BookStack/books/projets-due-2023-2024/page/le-sujet-du-projet)</span>.

**<span style="text-decoration: underline;">Exercice 1  
</span>***Dessiner des formes prédéfinies*

Le robot doit être capable de réaliser en 10 +- 0.2 secondes:

-Une ligne droite de 5cm  
-Une ligne droite de 5cm en pointillés  
-Un cercle de 2.5cm de rayon  
-Un cercle de 2.5cm de rayon en pointillés

<span style="text-decoration: underline;">**Exercice 2** </span>*Permettre à un utilisateur de dessiner*<span style="text-decoration: underline;">  
</span>

L'utilisateur doit être capable d'utiliser le robot pour dessiner la forme qu'il veut sur la zone de dessin. Le robot est contrôlé par un joystick qui doit donc être doté des fonctions utilisés dans l'exercice 1 (Déplacement, relever le stylo etc...)

#### Besoins

Il faut donc créer un robot qui:

- Maintienne un effecteur (le stylo) afin de dessiner
- Se déplace: 
    - Dans un plan horizontal: Créer les formes
    - Verticalement: Dessiner ou non, pour les pointillés
- Enregistre des formes prédéfinies
- Soit capable d'être contrôlé précisément par le joystick

#### Matériel  


Les moyens qu'on a à notre disposition sont les suivantes:

- Un crayon
- Interface de commande : 
    - Une carte arduino UNO avec câble USB-B;
    - Un joystick:
    - Une platine de protoypage;
    - Alimentation régulée 5V ;
    - Câbles, LEDs, boutons poussoirs, résistances.
- Motorisation : 
    - Deux servomoteurs HS422 180°;
    - Un servomoteur Emax ES08A 180°.
- Mécanique : 
    - Matière PLA pour impression 3D;
    - Feuilles medium : 3mm et 6mm d'épaisseur;
    - Vis et écrous : M2, M2.5, M3, M4.
    - Roulements et axes de diamètre 4mm.
- Informatique 
    - Ressources CAO.zip contient les fichiers Solidworks pour les deux modèles de servomoteurs
    - datasheets.zip contient les documentations de quelques-uns des composants fourni

#### Machines utilisées

Utilisation de l'impression 3D pour des pièces sofistqiues et éventuellement de la technologie de découpe laser pour les autres pieces.

### **Diagramme de GANTT**

Il y a un lien interactif qui est mis à jour à chaque modification via [https://airtable.com/appVydj1BDLSFj432/shrm5Cjk0diMBPmgL](https://airtable.com/appVydj1BDLSFj432/shrm5Cjk0diMBPmgL)

[![project-fablab-rob3-tasks-1.jpg](https://wiki.fablab.sorbonne-universite.fr/BookStack/uploads/images/gallery/2024-02/project-fablab-rob3-tasks-1.jpg)](https://wiki.fablab.sorbonne-universite.fr/BookStack/uploads/images/gallery/2024-02/project-fablab-rob3-tasks-1.png)[![project-fablab-rob3-tasks-2.jpg](https://wiki.fablab.sorbonne-universite.fr/BookStack/uploads/images/gallery/2024-02/project-fablab-rob3-tasks-2.jpg)](https://wiki.fablab.sorbonne-universite.fr/BookStack/uploads/images/gallery/2024-02/project-fablab-rob3-tasks-2.png)

<p class="callout info">**Nota bene**  
Ce diagramme de GANTT est donnée à titre indicatif</p>

[Project FabLab ROB3 Tasks (GANTT).pdf](https://wiki.fablab.sorbonne-universite.fr/BookStack/attachments/549)

### **Étape 1: Brainstorming, idées de réalisation et analyse des risques**  


Durant notre brainstorming: nous eûmes 5 idées que nous avons ultimement rejetées:

[![IMG_6529.png](https://wiki.fablab.sorbonne-universite.fr/BookStack/uploads/images/gallery/2024-02/scaled-1680-/img-6529.png)<span style="color: rgb(35, 111, 161);">*Figure 1: Photo de notre tableau - juste pour demonstration. Explications sont disponibles ci-dessous*</span>](https://wiki.fablab.sorbonne-universite.fr/BookStack/uploads/images/gallery/2024-02/img-6529.png)

<span style="color: rgb(34, 34, 34); font-family: var(--font-heading, var(--font-body)); font-size: 1.666em; font-weight: 400;">Idée 1 - Robot de roues</span>

<span style="text-decoration: underline;"><span style="color: rgb(0, 0, 0);">Principe:</span></span>

Un robot sur deux roues motorisées. Il peut faire de rotations en faisant tourner ses roues dans des directions opposées

- Le stylo est attaché au centre de de la plateforme.
- Les roues seraient contrôlées grâce aux 2 servomoteurs HS422 d'une façon similaire au robot E-PUC. Les servomoteurs sont connectés à la plateforme et aux roues via des biellettes ou des engrenages.
- Un servomoteur ES08A est utilisé pour contrôler le mécanisme de levée et de descente du stylo. Ce servomoteur est plus petit que les HS422 et peut être monté sur la plateforme à proximité du stylo.

<span style="text-decoration: underline;"><span style="color: rgb(0, 0, 0);">Croquis:</span></span>

[*![image.png](https://wiki.fablab.sorbonne-universite.fr/BookStack/uploads/images/gallery/2024-03/s2rimage.png)*](https://wiki.fablab.sorbonne-universite.fr/BookStack/uploads/images/gallery/2024-03/screenshot-2024-03-02-at-2-31-25-pm.png)[<span style="color: rgb(126, 140, 141);"><span style="color: rgb(35, 111, 161);">*Figure 2: Croquis du robot de* roues (type voiture avec une bille pour la stabilisation)</span></span>](https://wiki.fablab.sorbonne-universite.fr/BookStack/uploads/images/gallery/2024-03/screenshot-2024-03-02-at-2-31-25-pm.png)

<span style="text-decoration: underline;"><span style="color: rgb(0, 0, 0);">Avantages:</span></span>

- <span style="color: rgb(0, 0, 0);">Le robot est facile à controller avec un joystick (important pour la réalisation de l'exercise 2)</span>
- <span style="color: rgb(0, 0, 0);">Sa construction et modélisation est simple</span>

<span style="text-decoration: underline;"><span style="color: rgb(0, 0, 0);">Inconvenients: </span></span>

- On ne peut pas réaliser de trajectoires complexes. Le robot ne peut pas suivre des trajectoires complexes sans l'aide de capteurs odométriques.
- L'utilisation des servomoteurs empêcherait de faire rouler le robot indéfiniment. Cela ne serait pas un problème avec l'exercice 1. L'exercice 2 pourrait se révéler impossible à faire (Prenons par exemple un cas hyperbolique et fantaisiste: La forme à dessiner au joystick est une réplique de la Joconde. Le robot ne pourrait jamais faire ceci). Pour depaser cet obstacle, il faudrait utiliser de roues avec une diamétre assez grande entraînant des complications aux glissements sur la surface.

#### Idée 2 - Robot XY (cartésien)

<span style="text-decoration: underline;"><span style="color: rgb(0, 0, 0);">Principe:</span></span>

Un système similaire au fonctionnement d'une imprimante 3D:

- A l'aide d'un système de bielle manivelle, les deux servomoteurs HS422 commandent des liaisons glissières sur les axes x et y.
- La bielle tenant le stylo est elle même tenue par une bielle. Cette dernière se positionne sur la coordonnée de son axe, tandis que la bielle de l'effecteur choisit alors la deuxième coordonnée du point.
- Le servomoteur ES08A commande la levée et descente du stylo

<span style="text-decoration: underline;"><span style="color: rgb(0, 0, 0);">Croquis:</span></span>

[![image (1).png](https://wiki.fablab.sorbonne-universite.fr/BookStack/uploads/images/gallery/2024-03/image-1.png)*Figure 3: Le croquis d'un robot cartésien*](https://wiki.fablab.sorbonne-universite.fr/BookStack/uploads/images/gallery/2024-03/image-1.png)

<span style="text-decoration: underline;"><span style="color: rgb(0, 0, 0);">Avantages:</span></span>

- Cette solution ne présente pas de singularités dans sa configuration. De plus, les calculs sont simplifiés par le fait qu'on ne réfléchisse que sur le plan cartésien. Ce qui signifie qu'il peut atteindre toutes les positions du plan cartésien.
- Ce système permet un mouvement fluide et précis du stylo.
- Les calculs pour contrôler le robot sont simplifiés par le fait qu'on ne réfléchit que sur le plan cartésien sans faire ce changements de <span style="color: rgb(0, 0, 0);">bases.</span>

<span style="text-decoration: underline; color: rgb(0, 0, 0);">Inconvenients:</span>

- Le système de bielle-manivelle peut être plus lourd qu'un système à roues motorisées, ce qui peut affecter la performance du robot.
- Le système de bielle manivelle pourrait se révéler trop massif pour le robot.
- La solution consommerait beaucoup de matière

#### Idée 3 - Scissors mecanism

<span style="text-decoration: underline; color: rgb(0, 0, 0);">Principe:</span>

Inspirés du "Scissors mechanism", on voudrait attacher deux servomoteurs à la base du mécanisme et un système de commande d'actionneur au point "STYLO". Cette solution présente des avantages telles que :

<span style="text-decoration: underline; color: rgb(0, 0, 0);">Croquis:</span>

[![image (3).png](https://wiki.fablab.sorbonne-universite.fr/BookStack/uploads/images/gallery/2024-03/scaled-1680-/image-3.png)*Figure 4: Démonstration du mécanism de sciseaux*](https://wiki.fablab.sorbonne-universite.fr/BookStack/uploads/images/gallery/2024-03/image-3.png)

<span style="text-decoration: underline;"><span style="color: rgb(0, 0, 0); text-decoration: underline;">Avantages:</span></span>

- Le mécanisme "Scissors" permet d'avoir un espace d'écriture plus grand que les systèmes à roues motorisées ou à bielle-manivelle. Cela est dû à la tendance du mécanisme à s'étendre.
- De plus, ce mécanisme est particulièrement adapté à la création de cercles. La rotation des bras permet de dessiner des cercles de différentes tailles avec précision.
- En outre, le mécanisme "Scissors" permet de dessiner des lignes droites très précises dans le sens du mouvement du stylo.

<span style="text-decoration: underline; color: rgb(0, 0, 0);">Inconvenients:</span>

- Malheureusement, cette solution présente également un inconvénient. Les mouvements étant plutôt révolutionnaires, créer des lignes droites verticales du stylo semble limité et dans certains cas extrêmes impossible.

#### Idée 4 - Point d'intersection

<span style="text-decoration: underline; color: rgb(0, 0, 0);">Principe:</span>

Le robot sera doté d'un mécanisme de ciseaux alimenté par deux servo-moteurs positionnés aux coins de la base d'écriture. Chacun entraînera la rotation d'une poutre, permettant des mouvements de glissement dans les deux directions du vecteur r de rotation,. Le point d'intersection des deux poutres (créant ainsi une liaison glissière complexe) serait équipé du stylo, assurant une couverture totale de la feuille grâce à cette configuration ingénieuse.

<span style="text-decoration: underline; color: rgb(0, 0, 0);">Croquis:</span>

[![File_000.png](https://wiki.fablab.sorbonne-universite.fr/BookStack/uploads/images/gallery/2024-02/scaled-1680-/file-000.png)*Figure 5: Une conception de l'idée de point d'intersection*](https://wiki.fablab.sorbonne-universite.fr/BookStack/uploads/images/gallery/2024-02/file-000.png)

<span style="text-decoration: underline; color: rgb(0, 0, 0);">Inconvenients:</span>

- L'effort tangent au mouvement du stylo généré par une poutre sur l'autre serait extrêmement important, dépassant probablement les limites de faisabilité. La nécessité d'un glissement ultra-lisse, sans aucun frottement, et d'une précision extrême dans les mouvements représente un défi technique considérable.

#### Idée 5 - Robot type SCARA

<span style="text-decoration: underline; color: rgb(0, 0, 0);">Principe:</span>

On a pensé de faire un robot qui a deux axes de rotation verticales et une axe de rotation horizontale. En fait, il y aura deux rotations autour de deuz axes Z (Z1 et Z2) verticales et une troisieme rotation autour de Z3 qui est perpandiculier au axe (Z2).

<span style="text-decoration: underline;">Croquis:</span>

[![image (2).png](https://wiki.fablab.sorbonne-universite.fr/BookStack/uploads/images/gallery/2024-03/scaled-1680-/image-2.png)*Figure 6: croquis du robot avec 2 degrées de liberté*](https://wiki.fablab.sorbonne-universite.fr/BookStack/uploads/images/gallery/2024-03/image-2.png)

<span style="text-decoration: underline;">Avantages:</span>

- C'est un modèle connu du groupe, la partie mathématique est donc plus simple à réaliser
- Il y a beaucoup de manières de retirer de la matière avec une modélisation inteligente.

<span style="text-decoration: underline;">Inconvenients:</span>

- Poids excessive sur l'endroit du moteur 2, quelque chose qui pourrait impacter la precision de designs. Idéalement, on voudrait trouver une solution qui permettra de deplacer ce moteur sur le corps de la base principale du robot (oú se trouve le moteur 1) en utilisant les outils qu'on a à notre disposition.

#### Idée 6 - Robot parallélépipède

<span style="text-decoration: underline;">Principe:</span>

Inspiré par le mécanishm du robot type SCARA, on avait une reflexion: "Pourquoi on ne deplace pas le moteur de la 2éme rotation (moteur2), sur le même axe de rotation qui cellui du moteur 1. Le résultat du mouvement sera la même tout en ayant deplacé la majorité du poids sur le corps principale du robot.

<span style="text-decoration: underline;">Croquis:</span>

[![image.png](https://wiki.fablab.sorbonne-universite.fr/BookStack/uploads/images/gallery/2024-03/scaled-1680-/Km2image.png)Figure 7: Croquis du robot parallélépipède](https://wiki.fablab.sorbonne-universite.fr/BookStack/uploads/images/gallery/2024-03/Km2image.png)

<span style="text-decoration: underline;">Avantages:</span>

- Moins de poids sur les articulations mobiles du robot =&gt; meilleur précision par rapport l'idée d'avant.

<span style="text-decoration: underline;">Inconvenients:</span>

- Selon la manière d'expression du modèle géométrique direct, le calcul du modèle géométrique inverse pourrait être compliqué.
- La modélisation des quelques piéces unique pour la réalisation de ce type du robot pourrait augmenter le temps de fabrication et l'utilisation de matiére.

#### Solution retenue

Ayant effectué une évaluation approfondie des différentes alternatives, notre équipe a choisi de privilégier le développement d'un robot type parallélépipède pour la prochaine étape du projet. Cette décision est basée sur plusieurs points clés :

1. Robot de roues  
    
    - Pour s'assurer de la validité de la trajectoire, il faudrait l’équiper de capteurs odométrique. Nous ne disposons pas de ce matériel
    - L'utilisation des servomoteurs empêcherait de faire rouler le robot indéfiniment. Cela ne serait pas un problème avec l'exercice 1. L'exercice 2 pourrait se révéler impossible à faire (Prenons par exemple un cas hyperbolique et fantaisiste: La forme à dessiner au joystick est une réplique de la Joconde. Le robot ne pourrait jamais faire ceci)
2. Robot XY  
    
    - Le système de bielle manivelle pourrait se révéler trop massif pour le robot.
    - La solution consommerait beaucoup de matière
3. Robot "scissors"  
    
    - Selon la mécanique de la pièce, la création des lignes droites perpendiculaires du stylo n'est pas toujours possible à cause des mouvements révolutionnaires du mécanisme
    - Les déplacement sont limités à des trajectoires bien précises, ce qui rend le contrôle au joystick frustrant.
4. Robot intersection  
    
    - Il s'agit d'une idée très complète. Cependant, lorsque l'effecteur se trouve à l'extrémité des deux axes de guidage, il faut exercer une force massive pour l'en sortir et le faire revenir près des moteurs.  
        Nous pourrions contourner ce problème en faisant en sorte que les axes soient bien plus grand que la zone de travail. Mais: 
        - Cela impliquerait un ajout de matière, et donc de masse
        - Cela n'empêcherait pas un utilisateur au joystick de bloquer le robot
5. Robot type SCARA 
    - Il s'agit de notre idée de depart de base, mais à la découverte de l'idée numero 6 qui nous permetra de deplacer les deux moteur sur le corp de la base du robot, on a decidé de developer le robot type parallélépipède.

### **Étape 2: Conception détaillée**

#### Modèle géométrique

<p class="callout info">**Nota bene** On avait déjà commencé l'analyse du modéle cinematique du robot de l'idée numero 5 (type SCARA). Ci-dessous vous allez trouver l'option également de visualiser et voir le calcul qui était effectué pour ce robot, ainsi que pour le robot type parallélépipède (idée numero 6).</p>

<details id="bkmrk-robot-type-scara-cin"><summary>Robot type SCARA</summary>

### Cinématique

#### Schéma Cinématique + Tableau DH

<table border="1" id="bkmrk-solid-%CE%B8i%2B1-di%2B1-ai-%CE%B1" style="border-collapse: collapse; width: 100%;"><colgroup><col style="width: 20.0247%;"></col><col style="width: 20.0247%;"></col><col style="width: 20.0247%;"></col><col style="width: 20.0247%;"></col><col style="width: 20.0247%;"></col></colgroup><tbody><tr><td data-sheets-value="{"1":2,"2":"Solid"}" style="overflow: hidden; padding: 2px 3px 2px 3px; vertical-align: bottom;">**Solid**</td><td data-sheets-value="{"1":2,"2":"θi+1"}" style="overflow: hidden; padding: 2px 3px 2px 3px; vertical-align: bottom;">**ai**</td><td data-sheets-value="{"1":2,"2":"di+1"}" style="overflow: hidden; padding: 2px 3px 2px 3px; vertical-align: bottom;">**αi**</td><td data-sheets-value="{"1":2,"2":"ai"}" style="overflow: hidden; padding: 2px 3px 2px 3px; vertical-align: bottom;">**di+1**</td><td data-sheets-value="{"1":2,"2":"αi"}" style="overflow: hidden; padding: 2px 3px 2px 3px; vertical-align: bottom;">**θi+1**</td></tr><tr><td class="align-right" data-sheets-value="{"1":3,"3":0}" style="overflow: hidden; padding: 2px 3px 2px 3px; vertical-align: bottom; text-align: right;">0</td><td class="align-right" data-sheets-value="{"1":2,"2":"θ1"}" style="overflow: hidden; padding: 2px 3px 2px 3px; vertical-align: bottom;">0</td><td class="align-right" data-sheets-value="{"1":2,"2":"h1"}" style="overflow: hidden; padding: 2px 3px 2px 3px; vertical-align: bottom;">0</td><td class="align-right" data-sheets-value="{"1":3,"3":0}" style="overflow: hidden; padding: 2px 3px 2px 3px; vertical-align: bottom; text-align: right;">h1</td><td class="align-right" data-sheets-value="{"1":3,"3":0}" style="overflow: hidden; padding: 2px 3px 2px 3px; vertical-align: bottom; text-align: right;">θ1</td></tr><tr><td class="align-right" data-sheets-value="{"1":3,"3":1}" style="overflow: hidden; padding: 2px 3px 2px 3px; vertical-align: bottom; text-align: right;">1</td><td class="align-right" data-sheets-value="{"1":2,"2":"θ2"}" style="overflow: hidden; padding: 2px 3px 2px 3px; vertical-align: bottom;">L1</td><td class="align-right" data-sheets-value="{"1":2,"2":"h2"}" style="overflow: hidden; padding: 2px 3px 2px 3px; vertical-align: bottom;">-π/2</td><td class="align-right" data-sheets-value="{"1":2,"2":"L1"}" style="overflow: hidden; padding: 2px 3px 2px 3px; vertical-align: bottom;">h2</td><td class="align-right" data-sheets-value="{"1":3,"3":0}" style="overflow: hidden; padding: 2px 3px 2px 3px; vertical-align: bottom; text-align: right;">θ2-π/2</td></tr><tr><td class="align-right" data-sheets-value="{"1":3,"3":2}" style="overflow: hidden; padding: 2px 3px 2px 3px; vertical-align: bottom; text-align: right;">2</td><td class="align-right" data-sheets-value="{"1":2,"2":"-π/2"}" style="overflow: hidden; padding: 2px 3px 2px 3px; vertical-align: bottom;">0</td><td class="align-right" data-sheets-value="{"1":3,"3":0}" style="overflow: hidden; padding: 2px 3px 2px 3px; vertical-align: bottom; text-align: right;">0</td><td class="align-right" data-sheets-value="{"1":2,"2":"L2"}" style="overflow: hidden; padding: 2px 3px 2px 3px; vertical-align: bottom;">L2</td><td class="align-right" data-sheets-value="{"1":2,"2":"-π/2"}" style="overflow: hidden; padding: 2px 3px 2px 3px; vertical-align: bottom;">θ3</td></tr></tbody></table>

[![Schema cinématique du robot type SCARA](https://wiki.fablab.sorbonne-universite.fr/BookStack/uploads/images/gallery/2024-02/screenshot-2024-02-27-at-12-10-52-am.png)](https://wiki.fablab.sorbonne-universite.fr/BookStack/uploads/images/gallery/2024-02/img-0149.jpeg)Les deux premières liaisons, pour 𝑖∈{1,..,2}, sont des liaisons pivot d’axe (𝑂𝑖,𝑧𝑖). La troisième liaison est une liaison pivot d'axe aussi selon z3.

#### Modèle géométrique directe (complet)

Calculant T<sub>0-&gt;1</sub>, T<sub>1-&gt;2</sub>, T<sub>2-&gt;effector</sub>, ansi que T<sub>0-&gt;effector</sub>.

[![equations-scara-1.png](https://wiki.fablab.sorbonne-universite.fr/BookStack/uploads/images/gallery/2024-03/iNGequations-scara-1.png)](https://wiki.fablab.sorbonne-universite.fr/BookStack/uploads/images/gallery/2024-03/equations-scara-1.png)

[![Equations scara-2.jpg](https://wiki.fablab.sorbonne-universite.fr/BookStack/uploads/images/gallery/2024-03/equations-scara-2.jpg)](https://wiki.fablab.sorbonne-universite.fr/BookStack/uploads/images/gallery/2024-03/equations-scara-2.png)

Les résultas sont disponibles en PDF sur: [Matrices de transformation homogene.pdf](https://wiki.fablab.sorbonne-universite.fr/BookStack/attachments/571)

#### Modèle géométrique directe (simplifié)

On peut aussi se concentrer uniquement sur les deux premières rotations car ce sont elles qui donneront la position finale du stylo. Après un moment donné pour écrire ou non, on peut configurer cela en programmation. De cette façon, nous pouvons simplifier le calcul comme ci-dessous :

[![SCARA Simplified Robot-1.png](https://wiki.fablab.sorbonne-universite.fr/BookStack/uploads/images/gallery/2024-03/scaled-1680-/scara-simplified-robot-1.png)](https://wiki.fablab.sorbonne-universite.fr/BookStack/uploads/images/gallery/2024-03/scara-simplified-robot-1.png)

[![SCARA Simplified Robot-2.jpg](https://wiki.fablab.sorbonne-universite.fr/BookStack/uploads/images/gallery/2024-03/scaled-1680-/scara-simplified-robot-2.jpg)](https://wiki.fablab.sorbonne-universite.fr/BookStack/uploads/images/gallery/2024-03/scara-simplified-robot-2.jpg)

Les résultas sont disponibles en PDF sur: [SCARA Simplified Robot.pdf](https://wiki.fablab.sorbonne-universite.fr/BookStack/attachments/578)

#### Modèle géométrique inverse

Ainsi selon le modèle géométrique directe et le la trigonométrie du systéme:

[![Screenshot 2024-03-02 at 9.47.31 PM.png](https://wiki.fablab.sorbonne-universite.fr/BookStack/uploads/images/gallery/2024-03/scaled-1680-/screenshot-2024-03-02-at-9-47-31-pm.png)](https://wiki.fablab.sorbonne-universite.fr/BookStack/uploads/images/gallery/2024-03/screenshot-2024-03-02-at-9-47-31-pm.png)

[![Screenshot 2024-03-02 at 9.47.18 PM.png](https://wiki.fablab.sorbonne-universite.fr/BookStack/uploads/images/gallery/2024-03/scaled-1680-/screenshot-2024-03-02-at-9-47-18-pm.png)](https://wiki.fablab.sorbonne-universite.fr/BookStack/uploads/images/gallery/2024-03/screenshot-2024-03-02-at-9-47-18-pm.png)

</details><details id="bkmrk-robot-type-parall%C3%A9l%C3%A9"><summary>Robot type parallélépipède</summary>

#### Modèle géométrique directe

Ci-dessous vous pouvez trouver l'approche mathématique du robot type parallélépipède pour sa modèle géométrique directe.

[![Parallelipede-1.png](https://wiki.fablab.sorbonne-universite.fr/BookStack/uploads/images/gallery/2024-03/scaled-1680-/parallelipede-1.png)](https://wiki.fablab.sorbonne-universite.fr/BookStack/uploads/images/gallery/2024-03/parallelipede-1.png)

[![Parallelipede-2.jpg](https://wiki.fablab.sorbonne-universite.fr/BookStack/uploads/images/gallery/2024-03/parallelipede-2.jpg)](https://wiki.fablab.sorbonne-universite.fr/BookStack/uploads/images/gallery/2024-03/parallelipede-2.png)

Les résultas sont disponibles en PDF sur: [Paralléléplipède Robot.pdf](https://wiki.fablab.sorbonne-universite.fr/BookStack/attachments/572)

</details>
#### Schéma électronique

Sur notre schéma électronique il y a un bouton qui permet de changer entre mode manuelle et mode automatique. De plus, il y a deux LEDs qui indique sur quel mode on est un moment donnée. Par exemple si on est en mode manuelle, le LED bleu est allumé, sinon le LED vert est allumé. Em outre, vous pouvez aussi trouver la connection du joystick analogique qu'on a besoin pour la réalisation de l'exercice 2. Il faut noter que le joystick a un fonctionnement de bouton intégré. On peut utiliser cette fonctionnalité pour controller plean different chooses par exemple:

- Le stylo écrit ou pas.
- On fait un dessin avec le joystick qu'on visualise sur l'écran de l'ordinateur et on tap le bouton pour confirmer le dessin afin qu'il est créé par le robot.

[![image (4).png](https://wiki.fablab.sorbonne-universite.fr/BookStack/uploads/images/gallery/2024-03/scaled-1680-/image-4.png)Figure 8: Schéma électronique V1.0.0](https://wiki.fablab.sorbonne-universite.fr/BookStack/uploads/images/gallery/2024-03/image-4.png)

#### Modélisation

Notre objectif principal était de modéliser le robot selon un design à la fois compact et rigide. Un autre aspect important était de minimiser la quantité de matière utilisée et de réduire au maximum le temps de fabrication. Un modèle assemblé sur SolidWorks est disponible ci-dessous.

[![displayRobot.gif](https://wiki.fablab.sorbonne-universite.fr/BookStack/uploads/images/gallery/2024-03/displayrobot.gif)Figure 9: Demonstration du mécanisme du robot LineaScribe](https://wiki.fablab.sorbonne-universite.fr/BookStack/uploads/images/gallery/2024-03/displayrobot.gif)


##### Sous-assemblages

1. Bâti support
2. Articulations parallèles
3. Pivot joint
4. Pivot motor
5. Axe d'effecteur

##### Bâti support

C'est le corps principal du robot. Son objectif principal est de maintenir les deux moteurs sur le même axe de rotation. Il doit être capable de supporter les forces exercées par les moteurs vers les articulations parallèles ainsi que le retour d'information de ces forces.

[![Screenshot 2024-03-09 at 8.15.57 PM.png](https://wiki.fablab.sorbonne-universite.fr/BookStack/uploads/images/gallery/2024-03/scaled-1680-/screenshot-2024-03-09-at-8-15-57-pm.png)Figure 10: Bâti support du robot avec les moteur assemblés](https://wiki.fablab.sorbonne-universite.fr/BookStack/uploads/images/gallery/2024-03/screenshot-2024-03-09-at-8-15-57-pm.png)

Le bâti est entièrement créé en utilisant la découpe laser. Concernant la conception de la pièce, il faut noter que le plan du moteur du haut (moteur 1) est conceptualisé de manière à ne pas permettre le détachement des pièces tout en acceptant un stress excessif par les articulations principales du robot.

##### Articulations parallèles

Elles sont également entièrement conceptualisées pour la découpe laser (3 couches différentes de 3 mm). Elles sont montées sur les pièces "pivot joint" et "pivot motor" en utilisant des roulements 7201 BEGAP.

##### Pivot joint

Son rôle et la précision d'application sont essentiels pour le bon fonctionnement du robot. Il nous permet d'obtenir la distance correcte en parallélisme, comme indiqué dans le design ci-dessous. Il est entièrement créé en utilisant la découpe laser (2 couches de 3 mm).

[![Screenshot 2024-03-09 at 8.06.04 PM.png](https://wiki.fablab.sorbonne-universite.fr/BookStack/uploads/images/gallery/2024-03/scaled-1680-/8vMscreenshot-2024-03-09-at-8-06-04-pm.png)Figure 11: Focalisation sur la piéce "pivot joint"](https://wiki.fablab.sorbonne-universite.fr/BookStack/uploads/images/gallery/2024-03/8vMscreenshot-2024-03-09-at-8-06-04-pm.png)

##### Pivot motor

C'est la seule pièce qui est modélisée pour l'impression 3D. Son rôle est le même que celui de la pièce "pivot joint". Elle est directement montée sur le moteur du bas (moteur 2). Pour renforcer la partie de la pièce qui recevra les forces de frottement du stylo, un triangle de renfort a été ajouté, comme vous pouvez le voir ci-dessous.

[![Screenshot 2024-03-09 at 8.12.07 PM.png](https://wiki.fablab.sorbonne-universite.fr/BookStack/uploads/images/gallery/2024-03/scaled-1680-/screenshot-2024-03-09-at-8-12-07-pm.png)Figure 12: Triangle de renfort de "pivot motor"](https://wiki.fablab.sorbonne-universite.fr/BookStack/uploads/images/gallery/2024-03/screenshot-2024-03-09-at-8-12-07-pm.png)

<p class="callout info">L'axe centrique est un détail et il n'est pas requis pour le fonctionnement correct du mécanisme.</p>

<table border="1" id="bkmrk--13" style="border-collapse: collapse; width: 100%; height: 191.422px;"><colgroup><col style="width: 33.3539%;"></col><col style="width: 33.3539%;"></col><col style="width: 33.3539%;"></col></colgroup><tbody><tr style="height: 191.422px;"><td style="border-style: none; height: 191.422px;">[![Screenshot 2024-03-09 at 8.11.43 PM.png](https://wiki.fablab.sorbonne-universite.fr/BookStack/uploads/images/gallery/2024-03/scaled-1680-/screenshot-2024-03-09-at-8-11-43-pm.png)](https://wiki.fablab.sorbonne-universite.fr/BookStack/uploads/images/gallery/2024-03/screenshot-2024-03-09-at-8-11-43-pm.png)</td><td style="height: 191.422px; border-style: none;">[![Screenshot 2024-03-09 at 8.12.13 PM.png](https://wiki.fablab.sorbonne-universite.fr/BookStack/uploads/images/gallery/2024-03/scaled-1680-/screenshot-2024-03-09-at-8-12-13-pm.png)](https://wiki.fablab.sorbonne-universite.fr/BookStack/uploads/images/gallery/2024-03/screenshot-2024-03-09-at-8-12-13-pm.png)</td><td style="height: 191.422px; border-style: none;">[![Screenshot 2024-03-09 at 8.12.22 PM.png](https://wiki.fablab.sorbonne-universite.fr/BookStack/uploads/images/gallery/2024-03/scaled-1680-/screenshot-2024-03-09-at-8-12-22-pm.png)](https://wiki.fablab.sorbonne-universite.fr/BookStack/uploads/images/gallery/2024-03/screenshot-2024-03-09-at-8-12-22-pm.png)</td></tr></tbody></table>

#####  Axe d'effecteur

Il s'agit de l'axe qui supporte l'outil de l'effecteur. Il est guidé par les axes parallèles et mis en position (MIP) par la pièce "pivot joint". L'outil de l'effecteur est l'élément terminal du robot qui entre en contact direct avec la surface d'écriture. Son rôle principal est de tracer des lignes en utilisant un stylo.

<span style="background-color: rgb(251, 238, 184);"><span style="background-color: rgb(251, 238, 184);">EFFECTOR </span>WAITING TO BE UPLOADED</span>

##### Solidworks

Tous les fichiers et les fichiers d'assemblage sont disponibles sur: [LineaScribe Robot.zip](https://wiki.fablab.sorbonne-universite.fr/BookStack/attachments/614). Voici l'organisation des fichiers :

- **Architecture :** il s'agit d'un fichier squelette des différentes configurations. Si vous changez les dimensions des pièces présentes dans ce squelette, elles sont mises à jour dans tous les assemblages.
- **Assemblage bras &gt; liaison axe :** il s'agit de l'assemblage complet du mécanisme qui va se visser sur les actionneurs.
- **Assemblage &gt; Assemblage1 :** il s'agit de l'assemblage total du robot.
- **Assemblage effecteur &gt;** <span style="background-color: rgb(251, 238, 184);"><span style="background-color: rgb(251, 238, 184);">EFFECTOR </span>WAITING TO BE UPLOADED</span>

##### Fichiers SVG &amp; STL

1. [batis.svg](https://wiki.fablab.sorbonne-universite.fr/BookStack/attachments/609) (MDF 6mm)
2. [pivot joint.svg](https://wiki.fablab.sorbonne-universite.fr/BookStack/attachments/610) (MDF 3mm)
3. [bilette1.svg](https://wiki.fablab.sorbonne-universite.fr/BookStack/attachments/611) - articulation parallèle 1 (MDF 3mm)
4. [bilette2.svg](https://wiki.fablab.sorbonne-universite.fr/BookStack/attachments/612) - articulation parallèle 2 (MDF 3mm)
5. [pivot motor.STL](https://wiki.fablab.sorbonne-universite.fr/BookStack/attachments/613) (3D Maker PLA 30% infill - no support)
6. <span style="background-color: rgb(251, 238, 184);">EFFECTOR WAITING TO BE UPLOADED</span>

#### Pistes de programmation

[![FlowChart copy.drawio-1.png](https://wiki.fablab.sorbonne-universite.fr/BookStack/uploads/images/gallery/2024-03/scaled-1680-/flowchart-copy-drawio-1.png)Figure 13: Pistes de programmation version 1.0.0](https://wiki.fablab.sorbonne-universite.fr/BookStack/uploads/images/gallery/2024-03/flowchart-copy-drawio-1.png)

Document PDF V1.0.0: [FlowChart.pdf](https://wiki.fablab.sorbonne-universite.fr/BookStack/attachments/580)

#### Programmation

<p class="callout info">The program needs to be tested and be revised from every member of the group. Currently it respectes the "pistes de programmation" defined previously.  
  
Moreover, the program is not complete. This is only the base. Currently there is no control of the effector and it's tool.</p>

V1.0.0

```c++
#include <Servo.h>

const int buttonPin = 8;
const int ledAutoPin = 10;
const int ledManualPin = 9;
const int servo1Pin = 6;
const int servo2Pin = 5;
const int servo3Pin = 3;
const int joystickButtonPin = 7;
const int verticalJoystickPin = A1;
const int horizontalJoystickPin = A0;

Servo servo1;
Servo servo2;
Servo servo3;

int buttonState = 0;
int previousButtonState = 0;
int clickCount = 0;
int currentState = 0;

int trajectoryPoints[100][2];  // Array to store trajectory points
int trajectoryIndex = 0;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledAutoPin, OUTPUT);
  pinMode(ledManualPin, OUTPUT);
  pinMode(joystickButtonPin, INPUT_PULLUP);

  servo1.attach(servo1Pin);
  servo2.attach(servo2Pin);
  servo3.attach(servo3Pin);
}

void loop() {
  checkButton();
  if (clickCount == 1) {
    // Change state on single press
    currentState = (currentState == 1) ? 2 : 1;
    clickCount = 0;
  } else if (clickCount == 2) {
    // Execute current state on double press
    clickCount = 0;
    if (currentState == 1) {
      runAutomaticProgram();
      blinkLED(ledAutoPin);
    } else if (currentState == 2) {
      if (digitalRead(joystickButtonPin) == LOW) {
        executeTrajectory();
        blinkLED(ledManualPin);
      }
    }
  }
  // Light both LEDs while waiting for a state selection
  digitalWrite(ledAutoPin, HIGH);
  digitalWrite(ledManualPin, HIGH);
}

void checkButton() {
  buttonState = digitalRead(buttonPin);
  if (buttonState != previousButtonState && buttonState == LOW) {
    clickCount++;
  }
  previousButtonState = buttonState;
  // Turn off LEDs after button press is detected
  digitalWrite(ledAutoPin, LOW);
  digitalWrite(ledManualPin, LOW);
}

void runAutomaticProgram() {
  // Your code to move the servos in a predefined way
  // Example:
  for (int i = 0; i < 10; i++) {
    servo1.write(i * 10);
    servo2.write(90 - i * 5);
    servo3.write(180 - i * 15);
    delay(500);
  }
}

void captureTrajectory() {
  trajectoryPoints[trajectoryIndex][0] = analogRead(verticalJoystickPin);
  trajectoryPoints[trajectoryIndex][1] = analogRead(horizontalJoystickPin);
  trajectoryIndex++;
  if (trajectoryIndex >= 100) {
    trajectoryIndex = 0;
  }
}

void executeTrajectory() {
  for (int i = 0; i < 100; i++) {
    // Use trajectoryPoints[i][0] and trajectoryPoints[i][1] to move servos
    // Example:
    servo1.write(trajectoryPoints[i][0]);
    servo2.write(trajectoryPoints[i][1]);
    servo3.write(map(trajectoryPoints[i][1], 0, 1023, 0, 180));
    delay(100);
  }
}

void blinkLED(int ledPin) {
  for (int i = 0; i < 5; i++) {
    digitalWrite(ledPin, HIGH);
    delay(100);
  }
}
```

## Journal de bord / Calendrier  


*Avancée du projet à chaque étape, difficultés rencontrées, modifications et adaptations*

##### 14/02/2024

Discussion autour du Projet Robotique ROB3 - différents idées, décission, planning.

##### 16/02/2024

Provided a first kinematics schema and version 1 of DH table

##### 19/02/2024

Wiki: preliminary dossier was updated + DH: more detailed conception and corrected the table

##### 22/02/2024

Debut de modélisation des pieces du robot

##### 24/02/2024

Recherche sur les méthodes de géométrie inverse du robot

##### 02/03/2024

Finalisation de la partie modèle géométrique directe et inverse

##### 08/03/2024

Impression des pieces du bâtis support et on a lancé l'impression 3D du "pivot motor"
