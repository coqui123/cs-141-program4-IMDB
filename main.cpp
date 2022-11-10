
/**------------------------------------------

	Program 4: IMDB

	Course: CS 141, Fall 2022.
	System: MacOS using Clion
	Starter Code Author: Dr. Sara Riazi
	Student Author: ALEXANDER E. CARRILLO
-------------------------------------------*/

#include <iostream>
#include <cctype>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>
#include <algorithm>
#include <iomanip>


// global IMDB program namespace
namespace IMDB
{
	// gets menu input from the user for the initial menu
	auto get_menu_option() -> int
	{
		// prompt the user to enter the menu option
		int input;

		// prompt the user to enter the menu option
		std::cout << R"(Select a menu option:)"
			<< std::endl << R"(  1. Search for movies)"
			<< std::endl << R"(  2. Search for actors/actresses)"
			<< std::endl << R"(  3. Exit)"
			<< std::endl << R"(Your choice --> )";

		// read the menu option
		std::cin >> input;

		// cin fail check
		if (std::cin.fail())
		{
			std::cout << R"(Invalid input!)" << std::endl;
			return 3;
		}

		// return input
		return input;
	}

	// structs namespace for organizing the structs used in the program inside the main IMDB namespace
	namespace structs
	{
		// title_record struct has the information about the actors / actresses
		struct title_record
		{
			std::string t_const;
			std::string primary_title;
			std::string start_year;
			std::string genres;
		};

		// name_record struct has the information about the cast
		struct name_record
		{
			std::string n_const;
			std::string primary_name;
			std::string birth_year;
			std::string death_year;
			std::string primary_profession;
			std::string character_name;
			std::string known_for_titles;
		};

		// principal_record struct has the information about the cast
		struct principal_record
		{
			std::string t_const;
			std::string n_const;
			std::string categories;
			std::string job;
			std::string characters;
		};
	}

	// utils namespace which is accessed through the main IMDB namespace
	namespace utils
	{
		// The split_string function takes a line and split it on the delimiter and push the parts into items
		auto split_string(const std::string& line, const char delimiter, std::vector<std::string>& items) -> void
		{
			std::stringstream s_stream(line);
			while (s_stream.good())
			{
				std::string item;
				std::getline(s_stream, item, delimiter);
				items.emplace_back(item);
			}
		}

		// to_lower function takes a string and convert it to lower case
		auto to_lower(std::string str) -> std::string
		{
			std::transform(str.begin(), str.end(), str.begin(), tolower);
			return str;
		}

		// multi-use function possible using template for an is_equal check
		// instead of having one for each type I will be comparing
		template <typename T>
		auto is_equal(T a, T b) -> bool
		{
			return a == b;
		}

		// for look wrapper that repeats a function for a set amount of times
		template <class T>
		auto repeat_function(T function, const unsigned repetitions) -> void
		{
			// call function for the amount of repetitions using a for loop and iota function above
			for (auto& i : std::vector<int>(repetitions))
			{
				function();
			}
		}

		// files namespace inside of utils namespace inside of IMDB namespace
		namespace files
		{
			// The readTitleRecords function reads the title records from the file and stores them in the vector
			auto read_title_records(const std::string& file_name,
			                        std::vector<structs::title_record>& title_records) -> void
			{
				// open the file
				std::ifstream file(file_name);
				std::string line;
				std::getline(file, line);
				while (std::getline(file, line))
				{
					std::vector<std::string> items;
					// split the line on the delimiter
					split_string(line, '\t', items);
					structs::title_record title_record;
					title_record.t_const = items[0];
					title_record.primary_title = items[2];
					title_record.start_year = items[5];
					title_record.genres = items[8];
					// add the title record to the vector
					// using emplace_back because its 7.62% faster than push_back since were reading hundred megs of data ;D
					title_records.emplace_back(title_record);
				}
				// close the file
				file.close();
			}

			// The readNameRecords function reads the name records from the file and stores them in the vector
			auto read_name_records(const std::string& file_name,
			                       std::vector<structs::name_record>& name_records) -> void
			{
				// open the file
				std::ifstream file(file_name);
				std::string line;
				std::getline(file, line);
				while (std::getline(file, line))
				{
					std::vector<std::string> items;
					// split the line on the delimiter
					split_string(line, '\t', items);
					structs::name_record name_record;
					name_record.n_const = items[0];
					name_record.primary_name = items[1];
					name_record.birth_year = items[2];
					name_record.death_year = items[3];
					name_record.primary_profession = items[4];
					name_record.known_for_titles = items[5];
					// add the name record to the vector
					//using emplace_back because its 7.62% faster than push_back 
					name_records.emplace_back(name_record);
				}
				// close the file
				file.close();
			}

			//The readPrincipalRecords function reads the principal records from the file and stores them in the vector
			auto read_principal_records(const std::string& file_name,
			                            std::vector<structs::principal_record>& principal_records) -> void
			{
				// open the file
				std::ifstream file(file_name);
				std::string line;
				std::getline(file, line);
				while (std::getline(file, line))
				{
					std::vector<std::string> items;
					// split the line on the delimiter since its tsv
					split_string(line, '\t', items);
					structs::principal_record principal_record;
					principal_record.t_const = items[0];
					principal_record.n_const = items[2];
					principal_record.categories = items[3];
					principal_record.job = items[4];
					principal_record.characters = items[5];
					// add the principal record to the vector
					principal_records.emplace_back(principal_record);
				}
				// close the file
				file.close();
			}
		}
	}
}

// main run function called in main
auto run(const std::string& titles_file, const std::string& names_file, const std::string& principals_file) -> int
{
	// read the title records to vector
	std::vector<IMDB::structs::title_record> title_records;
	IMDB::utils::files::read_title_records(titles_file, title_records);

	// read the name records to vector
	std::vector<IMDB::structs::name_record> name_records;
	IMDB::utils::files::read_name_records(names_file, name_records);

	// read the principal records to vector
	std::vector<IMDB::structs::principal_record> principal_records;
	IMDB::utils::files::read_principal_records(principals_file, principal_records);

	// get the menu option and pass it through a switch case to handle the logic for the user input from the menu option
	switch (IMDB::get_menu_option())
	{
	// if the user enters 1, then search for movies
	case 1:
		{
			// turn all movie records to lower case into its own vector
			std::vector<IMDB::structs::title_record> title_records_lower;
			for (auto& title_record : title_records)
			{
				IMDB::structs::title_record title_record_lower;
				title_record_lower.t_const = title_record.t_const;
				title_record_lower.primary_title = IMDB::utils::to_lower(title_record.primary_title);
				title_record_lower.start_year = title_record.start_year;
				title_record_lower.genres = title_record.genres;
				// add the title record to the vector
				title_records_lower.emplace_back(title_record_lower);
			}

			// prompt the user to enter the movie name
			std::cout << R"(Enter search phrase: )";
			std::string movie_search;
			std::cin.ignore();

			// taking input with std::cin 
			std::cin >> movie_search;

			// cin fail check
			if (std::cin.fail())
			{
				std::cout << R"(Invalid input!)" << std::endl;
				break;
			}

			// turning user input to lower case for comparison
			movie_search = IMDB::utils::to_lower(movie_search);

			// split the search phrase into a vector of strings
			std::vector<std::string> movie_search_items;
			IMDB::utils::split_string(movie_search, '+', movie_search_items);

			// loop through the lower case title records and find the ones that match the lower case search phrase and add the non lower case movie information to a vector
			std::vector<IMDB::structs::title_record> movie_search_results;
			for (int i = 0; i < static_cast<int>(title_records_lower.size()); i++)
			{
				int match_count = 0;
				// looping through the split string above
				for (auto& movie_search_item : movie_search_items)
				{
					if (title_records_lower[i].primary_title.find(movie_search_item) != std::string::npos)
					{
						match_count++;
					}
				}
				if (IMDB::utils::is_equal<int>(match_count, static_cast<int>(movie_search_items.size())))
				{
					// add the title record to the vector
					movie_search_results.emplace_back(title_records[i]);
				}
			}

			// if there are no matches, print out "No match found!"
			if (movie_search_results.empty())
			{
				std::cout << R"(No match found!)" << std::endl;
			}

			// loop through movie search results genre and remove the , and replace it with a blank space
			for (auto& movie_search_result : movie_search_results)
			{
				std::string genre = movie_search_result.genres;
				// replaces text in the string
				std::replace(genre.begin(), genre.end(), ',', ' ');
				movie_search_result.genres = genre;
			}

			// new line to console
			std::cout << std::endl;

			// output records to console using old for loop just because i will be utilizing i in this case to get the loop iteration #
			for (int i = 0; i < static_cast<int>(movie_search_results.size()); i++)
			{
				std::cout << i << ": " << std::endl << R"(Title: )"
					<< movie_search_results[i].primary_title << std::endl
					<< R"(Year: )" << movie_search_results[i].start_year << std::endl
					<< R"(Genre: )" << movie_search_results[i].genres << std::endl;
				// use repeat function to print 15 R"(-)" to the console
				IMDB::utils::repeat_function([] { std::cout << R"(-)"; }, 15);
				std::cout << std::endl;
			}

			// ask the user to select a movie to see the actors for
			std::cout << R"(Select a movie to see its actors/actresses (-1 to go back to the previous menu): )";
			std::string movie_choice;
			std::cin >> movie_choice;

			// cin fail check
			if (std::cin.fail())
			{
				std::cout << R"(Invalid input!)" << std::endl;
				break;
			}

			// if the user enters a number that is not in the list of movies, print out "Invalid choice!"
			// if input is done return
			if (IMDB::utils::is_equal<std::string>(movie_choice, R"(done)"))
			{
				return run(titles_file, names_file, principals_file);
			}

			// if input is -1 return
			if (IMDB::utils::is_equal<std::string>(movie_choice, R"(-1)"))
			{
				return run(titles_file, names_file, principals_file);
			}

			// if input greater than options return
			if (std::stoi(movie_choice) > static_cast<int>(movie_search_results.size()))
			{
				std::cout << R"(Invalid choice!)" << std::endl;
				return run(titles_file, names_file, principals_file);
			}

			// if the user enters a valid number, print out the actors/actresses for that movie and their corresponding characters name
			std::vector<IMDB::structs::principal_record> match_name;
			for (auto& principal_record : principal_records)
			{
				if (IMDB::utils::is_equal<std::string>(principal_record.t_const,
				                                       movie_search_results[std::stoi(movie_choice)].t_const) && (
					IMDB::utils::is_equal<std::string>(principal_record.categories, R"(actor)") || IMDB::utils::is_equal<
						std::string>(principal_record.categories, R"(actress)")))
				{
					// add the principal record to the vector
					match_name.emplace_back(principal_record);
				}
			}

			// looping through name records and matching the nconst to the principal record
			for (auto& name_record : name_records)
			{
				// looping through matched name records
				for (auto& matched_record : match_name)
				{
					if (IMDB::utils::is_equal<std::string>(name_record.n_const, matched_record.n_const))
					{
						// output for this part
						std::cout << name_record.primary_name << R"( )" << matched_record.characters << std::endl;
					}
				}
			}

			// print out the list of actors/actresses for that movie
			// ask the user to select an actor/actress to see the movies they have been in
			std::cout <<
				R"(Select an actor/actress to see the movies they have been in (-1 to go to the previous menu): )";

			// getting user input
			int actor_choice;
			std::cin >> actor_choice;

			// cin fail check
			if (std::cin.fail())
			{
				std::cout << R"(Invalid input!)" << std::endl;
				break;
			}

			// if the user enters a number that is not in the list of actors/actresses, print out "Invalid choice!"
			if (IMDB::utils::is_equal<int>(actor_choice, -1))
			{
				return run(titles_file, names_file, principals_file);
			}

			// if input greater than options return
			if (actor_choice > static_cast<int>(match_name.size()))
			{
				std::cout << R"(Invalid choice!)" << std::endl;
				return run(titles_file, names_file, principals_file);
			}

			// if the user enters a valid number, print out the movies that the actor/actress has been in
			std::vector<IMDB::structs::principal_record> match_movie;
			for (auto& principal_record : principal_records)
			{
				if (IMDB::utils::is_equal<std::string>(principal_record.n_const,
				                                       match_name[actor_choice].n_const) && (IMDB::utils::is_equal
					<std::string>(principal_record.
					              categories, R"(actor)") || IMDB::utils::is_equal<std::string>(
						principal_record.categories, R"(actress)")))
				{
					// add the principal record to the vector
					match_movie.emplace_back(principal_record);
				}
			}

			// looping through title records
			for (auto& title_record : title_records)
			{
				// looping through matched movie records
				for (auto& matched_record : match_movie)
				{
					if (IMDB::utils::is_equal<std::string>(title_record.t_const, matched_record.t_const))
					{
						// outputting for this part of the program
						std::cout << title_record.primary_title << R"( )" << title_record.start_year << R"( )" <<
							matched_record.
							characters << std::endl;
					}
				}
			}
			break;
		}
	case 2:
		{
			// ask user to input string to search for
			std::cout << R"(Enter search phrase: )";
			std::string actor_search;
			std::cin.ignore();

			// grabbing input from user
			std::cin >> actor_search;

			// cin fail check
			if (std::cin.fail())
			{
				std::cout << R"(Invalid input!)" << std::endl;
				break;
			}

			// input to lower case using utils::to_lower
			actor_search = IMDB::utils::to_lower(actor_search);

			// split the search phrase into individual words
			std::vector<std::string> split_actor_search_items;
			IMDB::utils::split_string(actor_search, '+', split_actor_search_items);

			// making a copy of name records and its lower
			std::vector<IMDB::structs::name_record> name_records_lower;
			for (auto& record : name_records)
			{
				IMDB::structs::name_record name_record;
				name_record.n_const = record.n_const;
				name_record.primary_name = record.primary_name;
				// convert to lower case using utils::to_lower
				name_record.primary_name = IMDB::utils::to_lower(name_record.primary_name);
				// pushing back the lower case name to the vector
				name_records_lower.emplace_back(name_record);
			}

			// declaring a vector to hold the matched records
			std::vector<IMDB::structs::name_record> actor_search_results;

			// iterating through name_records_lower
			for (int i = 0; i < static_cast<int>(name_records_lower.size()); i++)
			{
				// match_count ticker
				int match_count = 0;

				// looping through the split string which we got using the provided split_string function
				for (auto& actor_search_item : split_actor_search_items)
				{
					if (name_records_lower[i].primary_name.find(actor_search_item) != std::string::npos)
					{
						match_count++;
					}
				}

				// checks if match count is equal to split_actor_search_items.size()
				if (IMDB::utils::is_equal<int>(match_count, static_cast<int>(split_actor_search_items.size())))
				{
					// add the name record to the vector
					actor_search_results.emplace_back(name_records[i]);
				}
			}

			// checks if vector is empty
			if (actor_search_results.empty())
			{
				std::cout << R"(No match found!)" << std::endl;

				return run(titles_file, names_file, principals_file);
			}

			// prints new line
			std::cout << std::endl;

			// use repeat function to print 15 R"(-)" to the console
			IMDB::utils::repeat_function([] { std::cout << R"(-)"; }, 15);

			// prints new line
			std::cout << std::endl;

			// not using a modern loop because didnt want to add extra
			// logic to the loop with a ticker that increments each repetition of the loop record felt more uniform this way
			for (int i = 0; i < static_cast<int>(actor_search_results.size()); i++)
			{
				std::cout << i << R"(: )" << std::endl
					<< actor_search_results[i].primary_name << std::endl
					<< actor_search_results[i].primary_profession << std::endl
					<< R"(()" << actor_search_results[i].birth_year << R"(-)"
					<< actor_search_results[i].death_year << R"())" << std::endl;

				// use repeat function to print 15 R"(-)" to the console
				IMDB::utils::repeat_function([] { std::cout << R"(-)"; }, 15);

				// prints new line
				std::cout << std::endl;
			}

			// menu output for this part asking for an input
			std::cout << R"(Select an actor/actress to see the movies they were in (-1 to go to the previous menu): )";
			int actor_choice;
			std::cin.ignore();

			// getting user input
			std::cin >> actor_choice;

			// cin fail check
			if (std::cin.fail())
			{
				// invalid input output
				std::cout << R"(Invalid input!)" << std::endl;
				break;
			}

			// checks if input is equal to -1 using my utils function defined above
			if (IMDB::utils::is_equal<int>(actor_choice, -1))
			{
				// return case if input is -1
				return run(titles_file, names_file, principals_file);
			}

			// checks if the user input bigger than the size of the search results vector
			if (actor_choice > static_cast<int>(actor_search_results.size()))
			{
				// invalid input output
				std::cout << R"(Invalid choice!)" << std::endl;
				return run(titles_file, names_file, principals_file);
			}

			// declaring a vector of matched principal records
			std::vector<IMDB::structs::principal_record> match_movie;

			// looping through principal records
			for (auto& principal_record : principal_records)
			{
				if (IMDB::utils::is_equal<std::string>(principal_record.n_const,
				                                        actor_search_results[actor_choice].n_const) && (
					IMDB::utils::is_equal<std::string>(principal_record.
					                                   categories, R"(actor)") || IMDB::utils::is_equal<std::string>(
						principal_record.categories, R"(actress)")))
				{
					// add the principal record to the vector
					match_movie.emplace_back(principal_record);
				}
			}

			// looping through title records to find the title of the movie etc.
			for (auto& title_record : title_records)
			{
				// looping through matched movies principal records
				for (auto& j : match_movie)
				{
					// checks if the movie record title record t_const is equal to the matched movie principal record t_const
					if (IMDB::utils::is_equal<std::string>(title_record.t_const, j.t_const))
					{
						// output for this part of the program
						std::cout << title_record.primary_title << R"( )" << title_record.start_year << R"( )" << j.
							characters << std::endl;
					}
				}
			}
			break;
		}
	case 3:
		break; // exit case exits program is input is 
	}

	// end of function return 0 to end program
	return 0;
}

auto main() -> int
{
	//Change these addresses according to your local machine
	const std::string titles_file = R"(movie.titles.tsv)";
	const std::string names_file = R"(movie.names.tsv)";
	const std::string principals_file = R"(movie.principals.tsv)";

	//DO NOT change the main function. The main function will be removed by the autograder
	run(titles_file, names_file, principals_file);
	return 0;
}
