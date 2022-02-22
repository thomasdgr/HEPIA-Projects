package trans

type Transaction struct{
  Id      uint32 `json:"id"`
  Sender  string `json:"sender"`
  Receiver string `json:"receiver"`
  Amount int32   `json:"amount"`
}
