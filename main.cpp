/*-------------------------------------
Program 2: MineSweeper

Course: CS 141, Fall 2022.
System: WINDOWS 11, Visual Studio 2022
Starter Code Author: Dr. Sara Riazi
Student Author: ALEXANDER E. CARRILLO
---------------------------------------*/

#include <iostream>
#include <cctype>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>
#include <algorithm>
#include <iomanip>

namespace utils
{

	//The split_string function takes a line and split it on the delimiter and push the parts into items
	void split_string(const std::string& line, const char delimiter, std::vector<std::string>& items)
	{
		std::stringstream s_stream(line);
		while (s_stream.good())
		{
			std::string item;
			std::getline(s_stream, item, delimiter);
			items.emplace_back(item);
		}
	}

	//to_lower function takes a string and convert it to lower case
	std::string to_lower(std::string str)
	{
		std::transform(str.begin(), str.end(), str.begin(), tolower);
		return str;
	}

	//gets menu input from the user for the initial menu
	int get_menu_option()
	{
		//prompt the user to enter the menu option
		int input;
		//prompt the user to enter the menu option
		std::cout << R"(Select a menu option:)"
			<< std::endl << R"(  1. Search for movies)"
			<< std::endl << R"(  2. Search for actors/actresses)"
			<< std::endl << R"(  3. Exit)"
			<< std::endl << R"(Your choice --> )";
		// read the menu option
		std::cin >> input;

		// return input
		return input;
	}

}

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
		std::string second_name;
		std::string category;
		std::string job;
		std::string characters;
	};

}

namespace files
{

	//The readTitleRecords function reads the title records from the file and stores them in the vector
	void read_title_records(const std::string& file_name, std::vector<structs::title_record>& title_records)
	{
		// open the file
		std::ifstream file(file_name);
		std::string line;
		std::getline(file, line);
		while (std::getline(file, line))
		{
			std::vector<std::string> items;
			// split the line on the delimiter
			utils::split_string(line, '\t', items);
			structs::title_record title_record;
			title_record.t_const = items[0];
			title_record.primary_title = items[2];
			title_record.start_year = items[5];
			title_record.genres = items[8];
			// add the title record to the vector
			//using emplace_back because its 7.62% faster than push_back since were reading hundred megs of data ;D
			title_records.emplace_back(title_record);
		}
		// close the file
		file.close();
	}

	//The readNameRecords function reads the name records from the file and stores them in the vector
	void read_name_records(const std::string& file_name, std::vector<structs::name_record>& name_records)
	{
		// open the file
		std::ifstream file(file_name);
		std::string line;
		std::getline(file, line);
		while (std::getline(file, line))
		{
			std::vector<std::string> items;
			// split the line on the delimiter
			utils::split_string(line, '\t', items);
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
	void read_principal_records(const std::string& file_name,
		std::vector<structs::principal_record>& principal_records)
	{
		// open the file
		std::ifstream file(file_name);
		std::string line;
		std::getline(file, line);
		while (std::getline(file, line))
		{
			std::vector<std::string> items;
			// split the line on the delimiter
			utils::split_string(line, '\t', items);
			structs::principal_record principal_record;
			principal_record.t_const = items[0];
			principal_record.second_name = items[2];
			principal_record.job = items[4];
			principal_record.category = items[3];
			principal_record.characters = items[5];
			// add the principal record to the vector
			principal_records.emplace_back(principal_record);
		}
		file.close();
	}

}

int run(const std::string& titles_file, const std::string& names_file, const std::string& principals_file)
{

	// read the title records from the file
	std::vector<structs::title_record> title_records;
	files::read_title_records(titles_file, title_records);

	// read the name records from the file
	std::vector<structs::name_record> name_records;
	files::read_name_records(names_file, name_records);

	// read the principal records from the file 
	std::vector<structs::principal_record> principal_records;
	files::read_principal_records(principals_file, principal_records);

	// get the menu option and pass it through a switch case to handle the logic for the user input from the menu option
	switch (utils::get_menu_option())
	{

		// if the user enters 1, then search for movies
	case 1:
	{

		//turn all movie records to lower case into its own vector
		std::vector<structs::title_record> title_records_lower;

		for (auto& title_record : title_records)
		{
			structs::title_record title_record_lower;
			title_record_lower.t_const = title_record.t_const;
			title_record_lower.primary_title = utils::to_lower(title_record.primary_title);
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

		//turning user input to lower case for comparison
		movie_search = utils::to_lower(movie_search);

		//split the search phrase into a vector of strings
		std::vector<std::string> movie_search_items;
		utils::split_string(movie_search, '+', movie_search_items);

		//loop through the lower case title records and find the ones that match the lower case search phrase and add the non lower case movie information to a vector
		std::vector<structs::title_record> movie_search_results;

		for (int i = 0; i < title_records_lower.size(); i++)
		{
			int match_count = 0;
			for (auto& movie_search_item : movie_search_items)
			{
				if (title_records_lower[i].primary_title.find(movie_search_item) != std::string::npos)
				{
					match_count++;
				}
			}
			if (match_count == movie_search_items.size())
			{
				// add the title record to the vector
				movie_search_results.emplace_back(title_records[i]);
			}
		}

		//if there are no matches, print out "No match found!"
		if (movie_search_results.empty())
		{
			std::cout << R"(No match found!)" << std::endl;
		}

		//print out the list of movies that match the search phrase
		//printout the movies that match search query
		//loop through movie search results genre and remove the , and replace it with a blank space
		for (auto& movie_search_result : movie_search_results)
		{
			std::string genre = movie_search_result.genres;
			std::replace(genre.begin(), genre.end(), ',', ' ');
			movie_search_result.genres = genre;
		}

		std::cout << std::endl;

		for (int i = 0; i < movie_search_results.size(); i++)
		{
			std::cout << i << ": " << std::endl << R"(Title: )"
				<< movie_search_results[i].primary_title << std::endl
				<< R"(Year: )" << movie_search_results[i].start_year << std::endl
				<< R"(Genre: )" << movie_search_results[i].genres << std::endl;
			// for loop to print out 15 dashes if not the last run no endl
			for (int j = 0; j < 15; j++)
			{
				std::cout << R"(-)";
			}
			std::cout << std::endl;
		}

		//ask the user to select a movie to see the actors for
		std::cout << R"(Select a movie to see its actors/actresses (-1 to go back to the previous menu): )";
		std::string movie_choice;
		std::cin >> movie_choice;

		//if the user enters a number that is not in the list of movies, print out "Invalid choice!"
		//goto start menu if -1
		if (movie_choice == R"(done)")
		{
			return run(titles_file, names_file, principals_file);
		}

		if (movie_choice == R"(-1)")
		{
			return run(titles_file, names_file, principals_file);
		}

		if (std::stoi(movie_choice) > movie_search_results.size())
		{
			std::cout << R"(Invalid choice!)" << std::endl;
			return run(titles_file, names_file, principals_file);
		}

		//if the user enters a valid number, print out the actors/actresses for that movie and their corresponding characters name
		std::vector<structs::principal_record> match_name;
		for (auto& principal_record : principal_records)
		{
			if ((principal_record.t_const == movie_search_results[std::stoi(movie_choice)].t_const) && (
				principal_record.category == "actor" || principal_record.category == "actress"))
			{
				// add the principal record to the vector
				match_name.emplace_back(principal_record);
			}
		}

		for (auto& name_record : name_records)
		{
			for (auto& j : match_name)
			{
				if (name_record.n_const == j.second_name)
				{
					// output for this part
					std::cout << name_record.primary_name << R"( )" << j.characters << std::endl;
				}
			}
		}

		//print out the list of actors/actresses for that movie
		//ask the user to select an actor/actress to see the movies they have been in
		std::cout <<
			R"(Select an actor/actress to see the movies they have been in (-1 to go to the previous menu): )";
		int actor_choice;

			// getting user input
		std::cin >> actor_choice;

		//if the user enters a number that is not in the list of actors/actresses, print out "Invalid choice!"
		if (actor_choice == -1)
		{
			return run(titles_file, names_file, principals_file);
		}

		if (actor_choice > match_name.size())
		{
			std::cout << R"(Invalid choice!)" << std::endl;
			return run(titles_file, names_file, principals_file);
		}

		//if the user enters a valid number, print out the movies that the actor/actress has been in
		std::vector<structs::principal_record> match_movie;
		for (auto& principal_record : principal_records)
		{
			if ((principal_record.second_name == match_name[actor_choice].second_name) && (principal_record.
				category == "actor" || principal_record.category == "actress"))
			{
				// add the principal record to the vector
				match_movie.emplace_back(principal_record);
			}
		}

		for (auto& title_record : title_records)
		{
			for (auto& j : match_movie)
			{
				if (title_record.t_const == j.t_const)
				{
					// outputting for this part of the program
					std::cout << title_record.primary_title << R"( )" << title_record.start_year << R"( )" << j.characters << std::endl;
				}
			}
		}

		break;
	}
	case 2:
	{
		//ask user to input string to search for
		std::cout << R"(Enter search phrase: )";
		std::string actor_search;
		std::cin.ignore();

		// grabbing input from user
		std::cin >> actor_search;

		// input to lower case using utils::to_lower
		actor_search = utils::to_lower(actor_search);
		// split the search phrase into individual words
		std::vector<std::string> actor_search_items;
		utils::split_string(actor_search, '+', actor_search_items);

		std::vector<structs::name_record> name_records_lower;

		for (auto& i : name_records)
		{
			structs::name_record name_record;
			name_record.n_const = i.n_const;
			name_record.primary_name = i.primary_name;
			// convert to lower case using utils::to_lower
			name_record.primary_name = utils::to_lower(name_record.primary_name);
			//pushing back the lower case name to the vector
			name_records_lower.emplace_back(name_record);
		}

		std::vector<structs::name_record> actor_search_results;

		for (int i = 0; i < name_records_lower.size(); i++)
		{
			// match_count ticker
			int match_count = 0;
			for (auto& actor_search_item : actor_search_items)
			{
				if (name_records_lower[i].primary_name.find(actor_search_item) != std::string::npos)
				{
					match_count++;
				}
			}
			if (match_count == actor_search_items.size())
			{
				// add the name record to the vector
				actor_search_results.emplace_back(name_records[i]);
			}
		}

		if (actor_search_results.empty())
		{
			std::cout << R"(No match found!)" << std::endl;
			return run(titles_file, names_file, principals_file);
		}

		std::cout << std::endl;

		//print 15 "/"
		//loop to print 15 -
		for (int i = 0; i < 15; i++)
		{
			std::cout << R"(-)";
		}

		std::cout << std::endl;

		for (int i = 0; i < actor_search_results.size(); i++)
		{
			std::cout << i << R"(: )" << std::endl
				<< actor_search_results[i].primary_name << std::endl
				<< actor_search_results[i].primary_profession << std::endl
				<< R"(()" << actor_search_results[i].birth_year << R"(-)"
				<< actor_search_results[i].death_year << R"())" << std::endl;
			for (int j = 0; j < 15; j++)
			{
				std::cout << R"(-)";
			}
			std::cout << std::endl;
		}
		// menu output for this part asking for an input
		std::cout << R"(Select an actor/actress to see the movies they were in (-1 to go to the previous menu): )";
		int actor_choice;
		std::cin.ignore();

		// getting user input
		std::cin >> actor_choice;

		if (actor_choice == -1)
		{
			return run(titles_file, names_file, principals_file);
		}

		if (actor_choice > actor_search_results.size() || actor_choice < 0)
		{
			std::cout << R"(Invalid choice!)" << std::endl;
			return run(titles_file, names_file, principals_file);
		}

		std::vector<structs::principal_record> match_movie;

		for (auto& principal_record : principal_records)
		{
			if ((principal_record.second_name == actor_search_results[actor_choice].n_const) && (principal_record.
				category == "actor" || principal_record.category == "actress"))
			{
				// add the principal record to the vector
				match_movie.emplace_back(principal_record);
			}
		}

		for (auto& title_record : title_records)
		{
			for (auto& j : match_movie)
			{
				if (title_record.t_const == j.t_const)
				{
					// output for this part of the program
					std::cout << title_record.primary_title << R"( )" << title_record.start_year << R"( )" << j.characters << std::endl;
				}
			}
		}

		break;
	}
	case 3: // exit case
	{
		return 0;
	}
	}
	return 0;
}


int main()
{
	//Change these addresses according to your local machine
	const std::string titles_file = R"(movie.titles.tsv)";
	const std::string names_file = R"(movie.names.tsv)";
	const std::string principals_file = R"(movie.principals.tsv)";

	//DO NOT change the main function. The main function will be removed by the autograder
	run(titles_file, names_file, principals_file);
	return 0;
}
