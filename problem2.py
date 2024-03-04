import pandas as pd
# I have no background in machine learning (i believe this question is one) so i just pretendent that the objects effects
#are independent and their win rate is based on the win rate of each one, calculated based on the csv file
# (if mango got 3 wins out of 6 its rate is 50% regardless of the rest)
# the syntax below is based on online resources 


#another solution can be calculating the rates based on tuple combinations 
#(mango and lion got 3 wins out of 6, the rate of using them together is 50% )
#This solution might give better answers since it conciders the overlapping
#however I believe there must be a way to iterate over the tuples in an efficient way that i am not
#aware of, since we will have so many tuples to consider

def individual_win_rates(data_file="prediction.csv"):
    """
    Calculates individual win rates for cards, animals, and fruits.

    """

    try:
        data = pd.read_csv(data_file)
    except FileNotFoundError:
        raise FileNotFoundError(f"CSV file '{data_file}' not found.")

    win_rates = {}

    # Card Rates
    card_rates = data.groupby('Card Suit')['Result'].mean().reset_index()
    card_rates.columns = ['Card Suit', 'Win Rate']
    win_rates['Cards'] = card_rates

    # Animal Rates
    animal_rates = data.groupby('Animal Name')['Result'].mean().reset_index()
    animal_rates.columns = ['Animal Name', 'Win Rate']
    win_rates['Animals'] = animal_rates

    # Fruit Rates
    fruit_rates = data.groupby('Fruit')['Result'].mean().reset_index()
    fruit_rates.columns = ['Fruit', 'Win Rate']
    win_rates['Fruits'] = fruit_rates

    return win_rates


def calculate_combination_rate_naive(suit, animal, fruit, data_file="prediction.csv"):
    """
    Calculates the product of individual win rates for a given combination,
   """
    try:
        win_rates = individual_win_rates(data_file)

        card_rate = win_rates['Cards'].loc[win_rates['Cards']['Card Suit'] == suit]['Win Rate'].values[0]
        animal_rate = win_rates['Animals'].loc[win_rates['Animals']['Animal Name'] == animal]['Win Rate'].values[0]
        fruit_rate = win_rates['Fruits'].loc[win_rates['Fruits']['Fruit'] == fruit]['Win Rate'].values[0]

        combined_rate = card_rate * animal_rate * fruit_rate

        return round(combined_rate, 2)

    except (KeyError, FileNotFoundError) as e:
        print(e)
        return 0

if __name__ == "__main__":
    suit = "Hearts"
    animal = "Lion"
    fruit = "Mango"

    try:
        probability = calculate_combination_rate_naive(suit, animal, fruit)
        print("Combined win rate using individual rates :", probability, "%")
    except Exception as e:
        print(e)
