#pragma once

#include <ostream>
#include <vector>

#include "nft.hh"

// A person
class Person
{
public:
    // Initiliaze its member attributes.
    Person(const std::string& name, uint money);

    // Returns the list of NFTs it owns.
    std::vector<std::string> enumerate_nfts() const;

    // Give it a NFT.
    void add_nft(NFT nft);
    // Take away a NFT.
    NFT remove_nft(const std::string& name);

    // Add money.
    void add_money(uint money);
    // Remove money, if possible.
    bool remove_money(uint money);

    // Getters for money and name.
    uint get_money() const;
    std::string get_name() const;

private:
    std::string name_;
    uint money_;
    std::vector<NFT> nfts_;
};

// Write informations about the person on the given stream.
std::ostream& operator<<(std::ostream& os, const Person& p);
