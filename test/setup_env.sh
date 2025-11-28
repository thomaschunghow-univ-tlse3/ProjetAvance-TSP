#!/bin/bash


# Créez un environnement virtuel
python3 -m venv venv

# Vérifiez si virtualenv est installé et installez-le si nécessaire
if ! [ -x "$(command -v virtualenv)" ]; then
    echo 'virtualenv is not installed. Installing virtualenv now...'
    pip install virtualenv
fi


# Créez un environnement virtuel
python3 -m venv venv


# Activez l'environnement virtuel
source venv/bin/activate

# Installez les paquets nécessaires

pip install -r test/requirements.txt

echo "Utiliser 'source venv/bin/activate' pour activer l'environnement virtuel. Utiliser 'deactivate' pour le désactiver."

pip install -r requirements.txt

echo "Environment setup is complete. Use 'source venv/bin/activate' to activate the virtual environment."

pip install -r requirements.txt

echo "Environment setup is complete. Use 'source venv/bin/activate' to activate the virtual environment."

pip install -r test/requirements.txt

echo "Utiliser 'source venv/bin/activate' pour activer l'environnement virtuel. Utiliser 'deactivate' pour le désactiver."

