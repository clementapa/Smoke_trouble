# Smoke_trouble
Le but du jeu est d'éteindre les fumée avec une lance à eau que l'avatar pompier doit placer au bon endroit.
Au debut du jeu, la lance crée des jets d'eau puis arrivé à un certain round pour augmenter la difficulté elle lance de l'eau simplement.

À chaque fois que l'eau touche une fumée la taille de celle-ci se divise en deux, si elle est encore touché elle se redivise en deux jusqu'à ce qu'elle atteigne une taille limite la faisant disparaître.

Le joueur augmente son score à chaque fois qu'il touche une fumée.
À chaque fois, qu'une fumée est éteinte celle-ci peut faire apparaître des bonus ou des malus.  
Le joueur perd une vie si il se fait touché par l'une des fumée ou si il n'éteind pas toute les fumées avant le temps imparti. Une fois que le joueur n'a plus de vie il perd la partie.  

Le jeu s'organise en round, augmentant la difficulté au fur et à mesure du jeu. (multiplier le nombre de fumée par deux à chaque round?)

Le score, le round et le nombre de vie du joueur doivent être affichés ainsi que le temps restant du round.

Bonus:
-piece: augmente le score du joueur.
-x2: multiplie le score que prend le joueur à chaque fois qu'il touche une fumée.
-life: le joueur gagne une vie en plus.

Avatar collision avec:  
- une smoke -> perte de vie.
- un bonus -> faire l'effet du bonus.

Smoke collision avec:
- les murs et sol -> rebond.
- l'avatar -> perte de vie avatar.
- water -> smoke se divise en 2.

Bonus collision avec:
- le sol genre on fait apparaître en l'air et le bonus va se mettre sur le sol.
- l'avatar -> faire l'effet du bonus.

Water collision avec:
- une smoke -> smoke se divise en 2.
