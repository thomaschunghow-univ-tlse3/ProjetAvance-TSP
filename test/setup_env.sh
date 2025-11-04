#!/bin/bash

<<<<<<< HEAD
<<<<<<< HEAD
# Créez un environnement virtuel
python3 -m venv venv
=======
=======
>>>>>>> f2faa0f (rebase)
# Vérifiez si virtualenv est installé et installez-le si nécessaire
if ! [ -x "$(command -v virtualenv)" ]; then
    echo 'virtualenv is not installed. Installing virtualenv now...'
    pip install virtualenv
fi

# Créez un environnement virtuel
virtualenv venv
<<<<<<< HEAD
>>>>>>> 20e72f5 (modification de l'arborescence)
=======
=======
# Créez un environnement virtuel
python3 -m venv venv
>>>>>>> be83f65a75bce54993f454634b1b4966b5da6798
>>>>>>> f2faa0f (rebase)

# Activez l'environnement virtuel
source venv/bin/activate

# Installez les paquets nécessaires
<<<<<<< HEAD
<<<<<<< HEAD
pip install -r test/requirements.txt

echo "Utiliser 'source venv/bin/activate' pour activer l'environnement virtuel. Utiliser 'deactivate' pour le désactiver."
=======
pip install -r requirements.txt

echo "Environment setup is complete. Use 'source venv/bin/activate' to activate the virtual environment."
>>>>>>> 20e72f5 (modification de l'arborescence)
=======
pip install -r requirements.txt

echo "Environment setup is complete. Use 'source venv/bin/activate' to activate the virtual environment."
=======
pip install -r test/requirements.txt

echo "Utiliser 'source venv/bin/activate' pour activer l'environnement virtuel. Utiliser 'deactivate' pour le désactiver."
>>>>>>> be83f65a75bce54993f454634b1b4966b5da6798
>>>>>>> f2faa0f (rebase)
