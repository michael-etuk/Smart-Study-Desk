import pandas as pd

data = pd.read_csv("study_data.csv")
data["Date"] = pd.to_datetime(data["Date"])

total_sessions = data["Sessions"].sum()
average_sessions = data["Sessions"].mean()

best_day = data.loc[data["Sessions"].idxmax()]

report = f"""
===== STUDY REPORT =====

Total Sessions: {int(total_sessions)}

Average Sessions: {average_sessions:.2f}

Best Study Day: {best_day['Date'].date()}

Sessions on Best Day: {int(best_day['Sessions'])}
"""

print(report)

with open("study_report.txt", "w") as file:
    file.write(report)

print("Report exported to study_report.txt")