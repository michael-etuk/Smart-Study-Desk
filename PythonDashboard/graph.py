import pandas as pd
import matplotlib.pyplot as plt

print("Loading data...")

data = pd.read_csv("study_data.csv")
data["Date"] = pd.to_datetime(data["Date"])

print(data)

# Statistics
total_sessions = data["Sessions"].sum()
average_sessions = data["Sessions"].mean()

daily_goal = 5

latest_sessions = data.iloc[-1]["Sessions"]

if latest_sessions >= daily_goal:
    goal_status = "GOAL ACHIEVED"
else:
    goal_status = f"Need {daily_goal - latest_sessions} More Sessions"

best_day = data.loc[data["Sessions"].idxmax()]

print("\n===== STUDY REPORT =====")
print("Total Sessions:", int(total_sessions))
print("Average Sessions:", round(average_sessions, 2))
print("Best Study Day:", best_day["Date"].date())
print("Sessions on Best Day:", int(best_day["Sessions"]))
print("Goal:", daily_goal)
print("Status:", goal_status)

# Graph
plt.figure(figsize=(8,5))

plt.plot(data["Date"], data["Sessions"], marker="o")

plt.axhline(
    y=average_sessions,
    linestyle="--",
    label=f"Average ({average_sessions:.2f})"
)

plt.title("Study Sessions Per Day")
plt.xlabel("Date")
plt.ylabel("Sessions")

plt.legend()

plt.xticks(rotation=45)

plt.tight_layout()

plt.show()