#!/bin/bash

# Créez un environnement virtuel
python3 -m venv venv

# Activez l'environnement virtuel
source venv/bin/activate

# Installez les paquets nécessaires
pip install -r test/requirements.txt

echo "Utiliser 'source venv/bin/activate' pour activer l'environnement virtuel. Utiliser 'deactivate' pour le désactiver."