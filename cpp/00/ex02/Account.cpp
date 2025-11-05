#include "Account.hpp"
#include <iostream>
#include <ctime>
#include <iomanip>

int Account::_nbAccounts = 0;
int Account::_totalAmount = 0;
int Account::_totalNbDeposits = 0;
int Account::_totalNbWithdrawals = 0;

int Account::getNbAccounts( void ) {
	return _nbAccounts;
}


int	Account::getTotalAmount( void ) {
	return _totalAmount;
}


int	Account::getNbDeposits( void ) {
	return _totalNbDeposits;
}


int	Account::getNbWithdrawals( void ) {
	return _totalNbWithdrawals;
}


void Account::displayAccountsInfos( void ) {
	Account::_displayTimestamp();
	std::cout << "accounts:" << _nbAccounts << ";"
	<< "total:" << _totalAmount << ";"
	<< "deposits:" << _totalNbDeposits << ";"
	<< "withdrawals:" << _totalNbWithdrawals << std::endl;
}

Account::Account( int initial_deposit ) 
	: _accountIndex(_nbAccounts), _amount(initial_deposit),
	_nbDeposits(0), _nbWithdrawals(0) 
{
	Account::_displayTimestamp();
	std::cout << "index:" << _accountIndex << ";"
	<< "amount:" << _amount << ";created" << std::endl;
	_nbAccounts++;
	_totalAmount += initial_deposit;
}

Account::~Account( void ) {
	Account::_displayTimestamp();
	std::cout << "index:" << _accountIndex << ";"
	<< "amount:" << _amount << ";closed" << std::endl;
}

void	Account::makeDeposit( int deposit ) {
	_nbDeposits++;
	_totalNbDeposits++;
	_amount += deposit;
	_totalAmount += deposit;
	Account::_displayTimestamp();
	std::cout << "index:" << _accountIndex << ";"
	<< "p_amount:" << _amount - deposit << ";"
	<< "deposit:" << deposit << ";"
	<< "amount:" << _amount << ";"
	<< "nb_deposits:" << _nbDeposits << std::endl;
}

bool	Account::makeWithdrawal( int withdrawal ) {
	if (_amount - withdrawal < 0) {
		Account::_displayTimestamp();
		std::cout << "index:" << _accountIndex << ";"
		<< "p_amount:" << _amount << ";"
		<< "withdrawal:refused" << std::endl;
		return false;
	}
	_nbWithdrawals++;
	_totalNbWithdrawals++;
	_amount -= withdrawal;
	_totalAmount -= withdrawal;
	Account::_displayTimestamp();
	std::cout << "index:" << _accountIndex << ";"
	<< "p_amount:" << _amount + withdrawal << ";"
	<< "withdrawal:" << withdrawal << ";"
	<< "amount:" << _amount << ";"
	<< "nb_withdrawals:" << _nbWithdrawals << std::endl;
	return true;
}

int		Account::checkAmount( void ) const {
	return _amount;
}

void	Account::displayStatus( void ) const {
	Account::_displayTimestamp();
	std::cout << "index:" << _accountIndex << ";"
	<< "amount:" << _amount << ";"
	<< "deposits:" << _nbDeposits << ";"
	<< "withdrawals:" << _nbWithdrawals << std::endl;
}

void	Account::_displayTimestamp( void ) {
		std::time_t t = std::time(NULL);  
		std::tm	*now = std::localtime(&t);   
		std::cout << "[" << now->tm_year + 1900
		<< std::setfill('0') << std::setw(2) << now->tm_mon + 1
		<< std::setw(2) << now->tm_mday << "_"
		<< std::setw(2) << now->tm_hour
		<< std::setw(2) << now->tm_min
		<< std::setw(2) << now->tm_sec
		<< "] ";
}