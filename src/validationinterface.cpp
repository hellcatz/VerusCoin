// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or https://www.opensource.org/licenses/mit-license.php .

#include "validationinterface.h"

static CMainSignals g_signals;

CMainSignals& GetMainSignals()
{
    return g_signals;
}

void RegisterValidationInterface(CValidationInterface* pwalletIn) {
    g_signals.UpdatedBlockTip.connect(boost::bind(&CValidationInterface::UpdatedBlockTip, pwalletIn, _1));
    g_signals.SyncTransaction.connect(boost::bind(&CValidationInterface::SyncTransaction, pwalletIn, _1, _2));
    g_signals.EraseTransaction.connect(boost::bind(&CValidationInterface::EraseFromWallet, pwalletIn, _1));
    g_signals.UpdatedTransaction.connect(boost::bind(&CValidationInterface::UpdatedTransaction, pwalletIn, _1));
    g_signals.RescanWallet.connect(boost::bind(&CValidationInterface::RescanWallet, pwalletIn));
    g_signals.SetBestChain.connect(boost::bind(&CValidationInterface::SetBestChain, pwalletIn, _1));
    g_signals.ChainTip.connect(boost::bind(&CValidationInterface::ChainTip, pwalletIn, _1, _2, _3, _4, _5));
    g_signals.Broadcast.connect(boost::bind(&CValidationInterface::ResendWalletTransactions, pwalletIn, _1));
    g_signals.BlockChecked.connect(boost::bind(&CValidationInterface::BlockChecked, pwalletIn, _1, _2));
    g_signals.ScriptForMining.connect(boost::bind(&CValidationInterface::GetScriptForMining, pwalletIn, _1));
}

void UnregisterValidationInterface(CValidationInterface* pwalletIn) {
    g_signals.ScriptForMining.disconnect(boost::bind(&CValidationInterface::GetScriptForMining, pwalletIn, _1));
    g_signals.BlockChecked.disconnect(boost::bind(&CValidationInterface::BlockChecked, pwalletIn, _1, _2));
    g_signals.Broadcast.disconnect(boost::bind(&CValidationInterface::ResendWalletTransactions, pwalletIn, _1));
    g_signals.ChainTip.disconnect(boost::bind(&CValidationInterface::ChainTip, pwalletIn, _1, _2, _3, _4, _5));
    g_signals.SetBestChain.disconnect(boost::bind(&CValidationInterface::SetBestChain, pwalletIn, _1));
    g_signals.RescanWallet.disconnect(boost::bind(&CValidationInterface::RescanWallet, pwalletIn));
    g_signals.UpdatedTransaction.disconnect(boost::bind(&CValidationInterface::UpdatedTransaction, pwalletIn, _1));
    g_signals.EraseTransaction.disconnect(boost::bind(&CValidationInterface::EraseFromWallet, pwalletIn, _1));
    g_signals.SyncTransaction.disconnect(boost::bind(&CValidationInterface::SyncTransaction, pwalletIn, _1, _2));
    g_signals.UpdatedBlockTip.disconnect(boost::bind(&CValidationInterface::UpdatedBlockTip, pwalletIn, _1));
}

void UnregisterAllValidationInterfaces() {
    g_signals.BlockFound.disconnect_all_slots();
    g_signals.ScriptForMining.disconnect_all_slots();
    g_signals.BlockChecked.disconnect_all_slots();
    g_signals.Broadcast.disconnect_all_slots();
    g_signals.ChainTip.disconnect_all_slots();
    g_signals.SetBestChain.disconnect_all_slots();
    g_signals.RescanWallet.disconnect_all_slots();
    g_signals.UpdatedTransaction.disconnect_all_slots();
    g_signals.EraseTransaction.disconnect_all_slots();
    g_signals.SyncTransaction.disconnect_all_slots();
    g_signals.UpdatedBlockTip.disconnect_all_slots();
}

void SyncWithWallets(const CTransaction &tx, const CBlock *pblock) {
    g_signals.SyncTransaction(tx, pblock);
}

void EraseFromWallets(const uint256 &hash) {
    g_signals.EraseTransaction(hash);
}

void RescanWallets() {
    g_signals.RescanWallet();
}