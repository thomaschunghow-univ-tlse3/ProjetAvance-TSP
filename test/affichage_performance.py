#
# affichage_performance.py
#

import pandas as pd
import matplotlib.pyplot as plt

ANALYSE_PERFORMANCE = "cache/analyse_performance_une_seconde.csv"
# ANALYSE_PERFORMANCE = "cache/analyse_performance_dix_seconde.csv"
# ANALYSE_PERFORMANCE = "cache/analyse_performance_une_minute.csv"


df = pd.read_csv(ANALYSE_PERFORMANCE, sep=";", engine="python")
df.columns = df.columns.str.strip()

# enlever lignes Moyenne, Q1, etc.
df_clean = df[~df["Instance"].str.contains("Moyenne|Q1|Médiane|Q3")]

methods = df_clean["Méthode"].unique()

fig, axes = plt.subplots(2, 3, figsize=(18, 12))
axes = axes.flatten()

for ax, method in zip(axes, methods):
    data = df_clean[df_clean["Méthode"] == method]["Différence (%)"]
    ax.hist(data, bins=len(data), color='skyblue', edgecolor='black')
    moyenne = data.mean()
    mediane = data.median()
    q1 = data.quantile(0.25)
    q3 = data.quantile(0.75)
    ax.axvline(moyenne, color='red', label=f'Moyenne = {moyenne:.2f}')
    ax.axvline(mediane, color='green', label=f'Médiane = {mediane:.2f}')
    ax.axvline(q1, color='orange', label=f'Q1 = {q1:.2f}')
    ax.axvline(q3, color='purple', label=f'Q3 = {q3:.2f}')
    ax.set_title(f"Différence (%) - {method}")
    ax.set_xlabel("Différence (%)")
    ax.set_ylabel("Nombre d'instances")
    ax.legend()

for i in range(len(methods), len(axes)):
    axes[i].axis('off')

plt.tight_layout()
plt.savefig("bin/performance_longueur.png", dpi=300)
plt.show()


fig, axes = plt.subplots(2, 3, figsize=(18, 12))
axes = axes.flatten()

for ax, method in zip(axes, methods):
    data = df_clean[df_clean["Méthode"] == method]["Temps CPU (s)"]
    ax.hist(data, bins=len(data), color='skyblue', edgecolor='black')
    moyenne = data.mean()
    mediane = data.median()
    q1 = data.quantile(0.25)
    q3 = data.quantile(0.75)
    ax.axvline(moyenne, color='red', label=f'Moyenne = {moyenne:.6f}')
    ax.axvline(mediane, color='green', label=f'Médiane = {mediane:.6f}')
    ax.axvline(q1, color='orange', label=f'Q1 = {q1:.6f}')
    ax.axvline(q3, color='purple', label=f'Q3 = {q3:.6f}')
    ax.set_title(f"Temps CPU (s) - {method}")
    ax.set_xlabel("Temps CPU (s)")
    ax.set_ylabel("Nombre d'instances")
    ax.legend()

# cases inutilisées
for i in range(len(methods), len(axes)):
    axes[i].axis('off')

plt.tight_layout()
plt.savefig("bin/performance_temps.png", dpi=300)
plt.show()
