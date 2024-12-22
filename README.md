# Airline Company Management System

## Overview

The Airline Company Management System is a software project designed to model the structure and operations of airline companies. Specifically developed to help airlines manage their resources effectively, the system oversees flights, planes, crew members, and passengers. It enforces organizational boundaries to ensure data integrity and coherence. 

## Project Structure

The project consists of several interconnected classes designed to represent the various entities associated with an airline:

- **Company**: The primary class that holds a list of flights. It maintains records of owned planes and employed crew members, ensuring that planes and crew cannot be assigned to multiple airline companies.
  
- **Flight**: Represents a flight with essential attributes such as flight ID, status, references to the associated plane, passengers, and crew members. Flight details include departure and arrival cities and times (in UTC milliseconds).

- **Plane**: Represents the planes owned by the airline, storing details like ID, name, and capacity requirements (including the number of passengers, stewardesses, and pilots necessary for operation).

- **Person**: A base class for passengers and crew members, containing common attributes such as ID, name, birthday, and gender.

- **Passenger and CrewMember**: These classes inherit from Person. Passenger class instances reference their flights, while CrewMember instances additionally store their roles (pilot or stewardess) to facilitate future extensions specific to crew functions.

## Features

- **Data Integrity**: The system prevents duplicate assignments of planes and crew members across different airlines.
  
- **Encapsulation**: Key operations like flight creation and destruction are encapsulated within the Company class, maintaining the integrity of flight management.
  
- **Extensibility**: The separation of the CrewMember class into specific roles allows for future enhancements tailored to pilots and stewardesses.

## UML Diagram

![UML Diagram](https://github.com/Konikelel/Airlines/blob/main/Documentation/Graph.jpg)
