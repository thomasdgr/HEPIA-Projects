# flute

## A propos

L'application a été développer et testé sur android studio. Nous avons mis les instructions uniquement des plateformes qui ont été testé, mais elle devrait tourner sur iOS et windows sans problème si les instructions de la documentation flutter sont bien suivies.

## Pour commencer

### Flutter

- Installer flutter pour votre système: <https://docs.flutter.dev/get-started/install>

### Tester l'application

#### Android

- Installer un emulator: <https://developer.android.com/studio/run/emulator?gclid=Cj0KCQiA2NaNBhDvARIsAEw55hgfl9AdvgWAHJuFI_cjzd6ByaAouxWWztMh8EwVj6mL1YxphzCQdVgaAt2PEALw_wcB&gclsrc=aw.ds> 
- Trouver l'adresse ip de l'ordinateur
- Mettre dans `flute/lib/Data/Routes.dart` l'adresse ip de l'ordinateur à la place de celle du serveur
- Lancer l'emulateur
- Depuis le dossier `flute` lancer `flutter run`
- L'application devrait compiler et s'installer sans problème

#### Chrome

Nous avons très peu testé avec Chrome
- Vérifier que chrome est sur le `path` de votre ordinateur
- Lancer `flutter run` depuis le dossier `flute`

## Notes Importantes

### Communication avec le serveur

Toutes les routes et l'adresse IP du serveur se trouve dans le `flute/lib/Data/routes.dart`.
Lors de test avec un emulateur il faut mettre l'adresse ip de l'ordinateur et s'assurer que le serveur **fastapi** est lancé sur l'adresse de loopback qui doit être `0.0.0.0`.
Si il y a une erreur du style 'Connection refused' alors c'est parce que l'ip n'est pas la bonne.

## Structure

Toute la logique se trouve dans le dossier `flute/lib`
- `flute/lib/main.dart`: le main de flutter qui démarre l'application
- `flute/lib/Data`: les datastructures, système pour communiquer avec api, gestion de json, etc...
- `flute/lib/Screens`: toutes les pages
- `flute/lib/Widgets`: Tout est widget en flutter et donc c'est utile de diviser parfois pour mieux réutiliser, ici il y a la barre de navigation
- `flute/lib/Utils`: les utilitaires, actuellement vide
- `flute/lib/Service`: concerne les services(ce qui tourne tout le temps), actuellement vide
