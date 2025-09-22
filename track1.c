<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Simple Habit Tracker</title>
    <style>
        * {
            margin: 0;
            padding: 0;
            box-sizing: border-box;
        }

        body {
            font-family: Arial, sans-serif;
            background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
            min-height: 100vh;
            padding: 20px;
        }

        .container {
            max-width: 800px;
            margin: 0 auto;
            background: white;
            border-radius: 15px;
            padding: 30px;
            box-shadow: 0 10px 30px rgba(0,0,0,0.2);
        }

        h1 {
            text-align: center;
            color: #333;
            margin-bottom: 30px;
            font-size: 2.5em;
        }

        .add-habit {
            display: flex;
            gap: 10px;
            margin-bottom: 30px;
            padding: 20px;
            background: #f8f9ff;
            border-radius: 10px;
            border: 2px dashed #667eea;
        }

        #habitInput {
            flex: 1;
            padding: 12px 15px;
            border: 2px solid #e0e0e0;
            border-radius: 8px;
            font-size: 16px;
            outline: none;
            transition: border-color 0.3s;
        }

        #habitInput:focus {
            border-color: #667eea;
        }

        #addBtn {
            background: #667eea;
            color: white;
            border: none;
            padding: 12px 20px;
            border-radius: 8px;
            cursor: pointer;
            font-size: 16px;
            font-weight: bold;
            transition: background 0.3s;
        }

        #addBtn:hover {
            background: #5a6fd8;
        }

        .habit-card {
            background: white;
            border: 2px solid #f0f0f0;
            border-radius: 12px;
            padding: 20px;
            margin-bottom: 15px;
            transition: all 0.3s ease;
            position: relative;
        }

        .habit-card:hover {
            transform: translateY(-2px);
            box-shadow: 0 5px 15px rgba(0,0,0,0.1);
        }

        .habit-header {
            display: flex;
            justify-content: space-between;
            align-items: center;
            margin-bottom: 15px;
        }

        .habit-name {
            font-size: 1.4em;
            font-weight: bold;
            color: #333;
        }

        .habit-streak {
            background: linear-gradient(45deg, #ff6b6b, #ffa500);
            color: white;
            padding: 5px 12px;
            border-radius: 15px;
            font-weight: bold;
            font-size: 0.9em;
        }

        .habit-days {
            display: flex;
            gap: 8px;
            flex-wrap: wrap;
            margin-bottom: 15px;
        }

        .day-circle {
            width: 35px;
            height: 35px;
            border-radius: 50%;
            display: flex;
            align-items: center;
            justify-content: center;
            cursor: pointer;
            font-weight: bold;
            transition: all 0.3s;
            border: 2px solid #e0e0e0;
            background: white;
        }

        .day-circle.completed {
            background: linear-gradient(45deg, #4CAF50, #45a049);
            color: white;
            border-color: #4CAF50;
            transform: scale(1.1);
        }

        .day-circle.today {
            border-color: #667eea;
            border-width: 3px;
        }

        .day-circle:hover {
            transform: scale(1.2);
            box-shadow: 0 3px 10px rgba(0,0,0,0.2);
        }

        .habit-controls {
            display: flex;
            gap: 10px;
            align-items: center;
        }

        .delete-btn {
            background: #ff4757;
            color: white;
            border: none;
            padding: 8px 15px;
            border-radius: 6px;
            cursor: pointer;
            font-size: 14px;
            transition: background 0.3s;
        }

        .delete-btn:hover {
            background: #ff3838;
        }

        .stats {
            background: linear-gradient(135deg, #f093fb 0%, #f5576c 100%);
            color: white;
            padding: 20px;
            border-radius: 12px;
            margin-bottom: 20px;
            text-align: center;
        }

        .stats h3 {
            margin-bottom: 15px;
            font-size: 1.3em;
        }

        .stats-grid {
            display: grid;
            grid-template-columns: repeat(auto-fit, minmax(150px, 1fr));
            gap: 15px;
        }

        .stat-item {
            background: rgba(255,255,255,0.2);
            padding: 15px;
            border-radius: 8px;
            backdrop-filter: blur(10px);
        }

        .stat-number {
            font-size: 2em;
            font-weight: bold;
            display: block;
        }

        .empty-state {
            text-align: center;
            padding: 40px;
            color: #666;
        }

        .empty-state h3 {
            margin-bottom: 10px;
            font-size: 1.5em;
        }

        @media (max-width: 600px) {
            .container {
                padding: 20px;
            }
            
            .add-habit {
                flex-direction: column;
            }
            
            .habit-days {
                justify-content: center;
            }
            
            .stats-grid {
                grid-template-columns: 1fr;
            }
        }
    </style>
</head>
<body>
    <div class="container">
        <h1>🎯 Simple Habit Tracker</h1>
        
        <div class="stats" id="stats">
            <h3>📊 Your Progress</h3>
            <div class="stats-grid">
                <div class="stat-item">
                    <span class="stat-number" id="totalHabits">0</span>
                    <span>Active Habits</span>
                </div>
                <div class="stat-item">
                    <span class="stat-number" id="todayCompleted">0</span>
                    <span>Completed Today</span>
                </div>
                <div class="stat-item">
                    <span class="stat-number" id="longestStreak">0</span>
                    <span>Longest Streak</span>
                </div>
                <div class="stat-item">
                    <span class="stat-number" id="totalCompletions">0</span>
                    <span>Total Completions</span>
                </div>
            </div>
        </div>

        <div class="add-habit">
            <input type="text" id="habitInput" placeholder="Enter a new habit (e.g., Drink 8 glasses of water)" maxlength="50">
            <button id="addBtn" onclick="addHabit()">➕ Add Habit</button>
        </div>

        <div id="habitsList"></div>
        
        <div class="empty-state" id="emptyState" style="display: none;">
            <h3>🌱 Start Your Journey!</h3>
            <p>Add your first habit above to begin tracking your progress.</p>
        </div>
    </div>

    <script>
        let habits = [];
        const DAYS_TO_SHOW = 14; // Show last 14 days

        // Load habits from localStorage on page load
        window.onload = function() {
            const saved = localStorage.getItem('simpleHabits');
            if (saved) {
                habits = JSON.parse(saved);
            }
            renderHabits();
            updateStats();
        };

        // Save habits to localStorage
        function saveHabits() {
            localStorage.setItem('simpleHabits', JSON.stringify(habits));
        }

        function addHabit() {
            const input = document.getElementById('habitInput');
            const habitName = input.value.trim();
            
            if (!habitName) {
                alert('Please enter a habit name!');
                return;
            }

            const habit = {
                id: Date.now(),
                name: habitName,
                completedDays: {},
                createdDate: new Date().toDateString()
            };

            habits.push(habit);
            input.value = '';
            saveHabits();
            renderHabits();
            updateStats();
        }

        function deleteHabit(habitId) {
            if (confirm('Are you sure you want to delete this habit?')) {
                habits = habits.filter(habit => habit.id !== habitId);
                saveHabits();
                renderHabits();
                updateStats();
            }
        }

        function toggleDay(habitId, dayKey) {
            const habit = habits.find(h => h.id === habitId);
            if (habit) {
                if (habit.completedDays[dayKey]) {
                    delete habit.completedDays[dayKey];
                } else {
                    habit.completedDays[dayKey] = true;
                }
                saveHabits();
                renderHabits();
                updateStats();
            }
        }

        function getDateKey(daysAgo = 0) {
            const date = new Date();
            date.setDate(date.getDate() - daysAgo);
            return date.toDateString();
        }

        function calculateStreak(habit) {
            let streak = 0;
            for (let i = 0; i < 365; i++) {
                const dateKey = getDateKey(i);
                if (habit.completedDays[dateKey]) {
                    streak++;
                } else {
                    break;
                }
            }
            return streak;
        }

        function renderHabits() {
            const habitsList = document.getElementById('habitsList');
            const emptyState = document.getElementById('emptyState');

            if (habits.length === 0) {
                habitsList.innerHTML = '';
                emptyState.style.display = 'block';
                return;
            }

            emptyState.style.display = 'none';
            
            habitsList.innerHTML = habits.map(habit => {
                const streak = calculateStreak(habit);
                const daysHTML = [];
                
                for (let i = DAYS_TO_SHOW - 1; i >= 0; i--) {
                    const dateKey = getDateKey(i);
                    const isCompleted = habit.completedDays[dateKey];
                    const isToday = i === 0;
                    const dayNumber = new Date(dateKey).getDate();
                    
                    daysHTML.push(`
                        <div class="day-circle ${isCompleted ? 'completed' : ''} ${isToday ? 'today' : ''}"
                             onclick="toggleDay(${habit.id}, '${dateKey}')"
                             title="${dateKey}${isToday ? ' (Today)' : ''}">
                            ${isCompleted ? '✓' : dayNumber}
                        </div>
                    `);
                }

                return `
                    <div class="habit-card">
                        <div class="habit-header">
                            <div class="habit-name">${habit.name}</div>
                            <div class="habit-streak">🔥 ${streak} day${streak !== 1 ? 's' : ''}</div>
                        </div>
                        <div class="habit-days">
                            ${daysHTML.join('')}
                        </div>
                        <div class="habit-controls">
                            <small style="color: #666;">Click circles to mark complete/incomplete</small>
                            <button class="delete-btn" onclick="deleteHabit(${habit.id})">🗑️ Delete</button>
                        </div>
                    </div>
                `;
            }).join('');
        }

        function updateStats() {
            const totalHabits = habits.length;
            const todayKey = getDateKey(0);
            const todayCompleted = habits.filter(habit => habit.completedDays[todayKey]).length;
            const longestStreak = Math.max(0, ...habits.map(calculateStreak));
            const totalCompletions = habits.reduce((sum, habit) => 
                sum + Object.keys(habit.completedDays).length, 0);

            document.getElementById('totalHabits').textContent = totalHabits;
            document.getElementById('todayCompleted').textContent = todayCompleted;
            document.getElementById('longestStreak').textContent = longestStreak;
            document.getElementById('totalCompletions').textContent = totalCompletions;
        }

        // Allow Enter key to add habit
        document.getElementById('habitInput').addEventListener('keypress', function(e) {
            if (e.key === 'Enter') {
                addHabit();
            }
        });
    </script>
</body>
</html>