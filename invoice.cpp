#include "invoice.h"

void Invoice::generateInvoice(const Client& sender, const Client& rec, const Route& route, const QString& dir) {
    QTextDocument doc;

    QString name = rec.getFullName();
    QString adress = route.getDestination();
    QString contact = rec.getEmail();
    QString contact2 = rec.getPhone();
    QString date = QDate::currentDate().toString("dd.MMM.yyyy");
    QString source = route.getSource().toUpper();
    QString destination = route.getDestination().toUpper();
    QString packagename = sender.getPackage().getPackageName().toUpper();
    QString packageID = QString::number(sender.getPackage().getCode());
    QString price = QString::number(route.getTotalPriceWithPackage(sender.getPackage()));
    QString distance = QString::number(route.getDistance());

    QString outputFileURI = dir + "/xCourier[" + packageID + "] " + name + date + ".pdf";

    doc.setHtml("<html lang=\"en\"><head>"
                  "<meta charset=\"UTF-8\">"
                  "<title>Editable Invoice</title>"
              "<style type=\"text/css\">"
              "* { margin: 0; padding: 0; }"
              "body { font: 14px/1.4 Georgia, serif; }"
              "#page-wrap { width: 800px; margin: 0 auto; }"
              "textarea { border: 0; font: 14px Georgia, Serif; overflow: hidden; resize: none; }"
              "table { border-collapse: collapse; }"
              "table td, table th { border: 1px solid black; padding: 5px; }"
              "#header { height: 15px; width: 100%; margin: 20px 0; background: #222; text-align: center; color: white; font: bold 15px Helvetica, Sans-Serif;"
                  " text-decoration: uppercase; letter-spacing: 20px; padding: 8px 0px; }"
              "#address { width: 250px; height: 150px; float: left; }"
              "#customer { overflow: hidden; }"
              "#logo { text-align: right; float: right; position: relative; margin-top: 25px; border: 1px solid #fff; max-width: 540px; max-height: 100px; overflow: hidden; }"
              "#logo:hover, #logo.edit { border: 1px solid #000; margin-top: 0px; max-height: 125px; }"
              "#logoctr { display: none; }"
              "#logo:hover #logoctr, #logo.edit #logoctr { display: block; text-align: right; line-height: 25px; background: #eee; padding: 0 5px; }"
              "#logohelp { text-align: left; display: none; font-style: italic; padding: 10px 5px;}"
              "#logohelp input { margin-bottom: 5px; }"
              ".edit #logohelp { display: block; }"
              ".edit #save-logo, .edit #cancel-logo { display: inline; }"
              ".edit #image, #save-logo, #cancel-logo, .edit #change-logo, .edit #delete-logo { display: none; }"
              "#customer-title { font-size: 20px; font-weight: bold; float: left; }"
              "#meta { margin-top: 1px; width: 300px; float: right; }"
              "#meta td { text-align: right;  }"
              "#meta td.meta-head { text-align: left; background: #eee; }"
              "#meta td textarea { width: 100%; height: 20px; text-align: right; }"
              "#items { clear: both; width: 100%; margin: 30px 0 0 0; border: 1px solid black; }"
              "#items th { background: #eee; }"
              "#items textarea { width: 80px; height: 50px; }"
              "#items tr.item-row td { border: 0; vertical-align: top; }"
              "#items td.description { width: 300px; }"
              "#items td.item-name { width: 175px; }"
              "#items td.description textarea, #items td.item-name textarea { width: 100%; }"
              "#items td.total-line { border-right: 0; text-align: right; }"
              "#items td.total-value { border-left: 0; padding: 10px; }"
              "#items td.total-value textarea { height: 20px; background: none; }"
              "#items td.balance { background: #eee; }"
              "#items td.blank { border: 0; }"
              "#terms { text-align: center; margin: 20px 0 0 0; }"
              "#terms h5 { text-transform: uppercase; font: 13px Helvetica, Sans-Serif; letter-spacing: 10px; border-bottom: 1px solid black; padding: 0 0 8px 0; margin: 0 0 8px 0; }"
              "#terms textarea { width: 100%; text-align: center;}"
              "textarea:hover, textarea:focus, #items td.total-value textarea:hover, #items td.total-value textarea:focus, .delete:hover { background-color:#EEFF88; }"
              ".delete-wpr { position: relative; }"
              ".delete { display: block; color: #000; text-decoration: none; position: absolute; background: #EEEEEE; font-weight: bold; padding: 0px 3px;"
                  " border: 1px solid; top: -6px; left: -22px; font-family: Verdana; font-size: 12px; }"
              "</style></head>"
              "<body data-pinterest-extension-installed=\"cr1.37\"> <br><br><br><br><br><br>"
                  "<div id=\"page-wrap\">"
                      "<div id=\"identity\">"
                          "<textarea id=\"address\">" + name + "<br>" //here
              "Adress: " + adress + "<br>"
              "Email: " + contact + "<br>"
              "Phone: " + contact2 + "</textarea><br><br>"
                      "</div>"
                      "<div style=\"clear:both\"></div>"
                      "<div id=\"customer\">"
                          "<textarea id=\"customer-title\">Thank you for shipping with us!<br>X-Courier,</textarea><br><br>" //here
                          "<table id=\"meta\">"
                              "<tbody><tr>"
                                  "<td class=\"meta-head\">Invoice #</td>"
                                  "<td><textarea>" + packageID + "</textarea></td>" //here
                              "</tr>"
                              "<tr>"
                                  "<td class=\"meta-head\">Date</td>"
                                  "<td><textarea id=\"date\">" + date + "</textarea></td>" //here
                              "</tr>"
                              "<tr>"
                                  "<td class=\"meta-head\">Amount Due</td>"
                                  "<td><div class=\"due\">RON " + price + "</div></td>" //here
                              "</tr>"
                          "</tbody></table>"
                      "</div>"
                      "<table id=\"items\">"
                        "<tbody><tr>"
                            "<th>Item</th>"
                            "<th>Description</th>"
                            "<th>Unit Cost</th>"
                            "<th>Quantity</th>"
                            "<th>Price</th>"
                        "</tr>"
                        "<tr class=\"item-row\">"
                            "<td class=\"item-name\"><div class=\"delete-wpr\"><textarea>Shipping</textarea></div></td>"
                            "<td class=\"description\"><textarea>Delivered " + packagename + " from " + source + " to " + destination + " (" + distance + "km)</textarea></td>" //here
                            "<td><textarea class=\"cost\">RON " + price + "</textarea></td>" // here
                            "<td><textarea class=\"qty\">1</textarea></td>"
                            "<td><span class=\"price\">RON " + price + "</span></td>" //here
                        "</tr>"
                        "<tr id=\"hiderow\">"
                          "<td colspan=\"5\"></td>"
                        "</tr>"
                        "<tr>"
                            "<td colspan=\"2\" class=\"blank\"> </td>"
                            "<td colspan=\"2\" class=\"total-line\">Subtotal</td>"
                            "<td class=\"total-value\"><div id=\"subtotal\">RON " + price + "</div></td>" //here
                        "</tr>"
                        "<tr>"
                            "<td colspan=\"2\" class=\"blank\"> </td>"
                            "<td colspan=\"2\" class=\"total-line\">Total</td>" //here
                            "<td class=\"total-value\"><div id=\"total\">RON " + price + "</div></td>"
                        "</tr>"
                        "<tr>"
                            "<td colspan=\"2\" class=\"blank\"> </td>"
                            "<td colspan=\"2\" class=\"total-line\">Amount Paid</td>"
                            "<td class=\"total-value\"><textarea id=\"paid\">RON 0.00</textarea></td>"
                        "</tr>"
                        "<tr>"
                            "<td colspan=\"2\" class=\"blank\"> </td>"
                            "<td colspan=\"2\" class=\"total-line balance\">Balance Due</td>"
                            "<td class=\"total-value balance\"><div class=\"due\">RON " + price + "</div></td>" //here
                        "</tr>"
                      "</tbody></table>"
                      "<div id=\"terms\">"
                        "<h5>Terms</h5>"
                        "<textarea>NET 30 Days. Finance Charge of 25.5% will be made on unpaid balances after 30 days.</textarea>"
                      "</div>"
                  "</div>"
              "</body></html>");

       QPrinter printer;
       printer.setOutputFileName(outputFileURI); qDebug() << "Invoice successfully saved in " << outputFileURI;
       printer.setOutputFormat(QPrinter::PdfFormat);
       doc.print(&printer);
       printer.newPage();
}
