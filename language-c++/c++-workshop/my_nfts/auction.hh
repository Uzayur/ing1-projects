#pragma once

#include "nft.hh"
#include "person.hh"

// Smart contract to auction a NFT.
// It is a RAII class.
class Auction
{
public:
    // Start the auction with the given (non-null) NFT.
    Auction(Person& organizer, NFT nft, uint initial_bid);
    // Close the auction.
    ~Auction();

    // https://en.cppreference.com/w/cpp/language/rule_of_three
    Auction(const Auction&&) = delete;
    Auction(const Auction&) = delete;
    Auction& operator=(const Auction&) = delete;

    // Allow a person to bid at the auction.
    bool bid(Person& person, uint money);

    // Getters for the nft name and highest bid.
    std::string get_nft_name() const;
    uint get_highest_bid() const;

private:
    Person& organizer_;
    NFT nft_;
    Person* highest_bidder_;
    uint highest_bid_;
};
