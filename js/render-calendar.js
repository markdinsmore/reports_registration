/**
 * Created by: Nathan Healea
 * Project: report_registration
 * File: render-calendar.js
 * Date: 4/13/16
 * Time: 11:42 AM
 */

$(document).ready(function () {
    
    this.option= {
        id: Drupal.settings.reportsregistration.studentid,
        event: JSON.parse(Drupal.settings.reportsregistration.studentpost)
    };
    var cal = new TACAL(this.option);
    cal.displayVars();
    cal.showcurr();
    
});